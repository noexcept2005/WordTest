#define USINGABB
#include <stdcjz.h>

#define WORDS_PATH	"CODING.txt"
#define OPTION_CNT 5		//ѡ������ 


#define XCPT_L try{
#define XCPT_R }catch(exception& e)	\
				{							\
					SetColor(12,0);		\
					cout<<"\n�����쳣:";		\
					SetColor(13,0);	\
					cout<<"\n"<<e.what();	\
					cout<<"\n";	\
					getch();	\
					SetColor(7,0);	\
					exit(0);	\
				}

HWND hwnd;
struct Word {
	string en;
	string ch;
};
//vector<Word> words;

struct Dictionary {
	string name;
	vector<Word> words;
};
vector<Dictionary> dicts;

bool ReadDictionary(string name)
{
	XCPT_L
	
	Dictionary dic;
	dic.name = name ;
	/*if(!ExistFile(WORDS_PATH))
	{
		SetColor(12,0);
		cout<<"\n���󣺵������ݶ�ʧ";
		return false;
	}*/
	vector<string> lines = ReadFileLines(".\\"+name);
	if(lines.empty())
		return false;
	int i=0;
	SetColor(11,0);
	while(i<lines.size())
	{
		string line = lines.at(i);
		stringstream ss;
		ss << line;
		//cout<<"\n"<<line;
		
		string en,ch;
		ss >> en >> ch;
		if(ss.fail())
		    break;
		Word word;
		word.en = en;
		word.ch = ch;
		dic.words.push_back(word);
		++i;
	}
	dicts.push_back(dic);
	return true;
	XCPT_R
}
bool ReadData(void)
{
	if(!dicts.empty())
		dicts.clear();
	_finddata_t fileDir;
	//stringstream ss;
	//ss<<dir<<"*.*";
	string dirp="*.txt";
	long lfDir;
	int i=0;
	if((lfDir = _findfirst(dirp.c_str(),&fileDir))==-1l)
	{
		return false;
	}
    else{
        do{
        	if(!strequ(fileDir.name,".") && !strequ(fileDir.name,".."))
			{
				ReadDictionary(fileDir.name);
			}
        }while( _findnext( lfDir, &fileDir ) == 0 );
    }
    _findclose(lfDir);
    return true;
}/*
void ListWords(void)
{
	repeatwith_zero(i,words.size()) 
	{
		SetColor(7,0);
		cout<<"\n"<<words.at(i).en;
		SetColor(15,0);
		cout<<"\t"<<words.at(i).ch;
	}
}*/
template <typename _T>
_T RandomChoice(initializer_list<_T> choices)
{
	vector<_T> vc(choices);
	if(vc.empty())
	    return _T(0);
	return vc.at(RandomRange(0,vc.size()-1));
}
void Start(string name)
{
	int _i=-1;
	for(int i=0;i<dicts.size();++i)
	{
		if(dicts.at(i).name == name)
		{
			_i = i;
			break;
		}
	}
	if(_i < 0)
		return;
	Dictionary& dict = dicts.at(_i);
	int n=1;
	int right_cnt = 0, wrong_cnt = 0;
	while(true)
	{
		Word wd = dict.words.at(RandomRange(0,dict.words.size()-1));
		SetColor(RandomChoice<UINT>({10,11,11,13,14,15}),0);
		cout<<"\n"<<n<<".";
		SetColor(14,0);
		cout<<" "<<wd.ch;
		SetColor(RandomChoice<UINT>({10,11,12,13,13}),0);
		cout<<" ?";
		
		int p = RandomRange(0,OPTION_CNT-1);
		
		UINT _optclr = RandomChoice<UINT>({7,8,10,11,11,14,15,15});
		for(int i=0;i<OPTION_CNT;++i)
		{
			Word opt;
			do{
				opt = dict.words.at(RandomRange(0,dict.words.size()-1));
			}while(opt.en == wd.en || opt.ch == wd.ch);
			SetColor(15,0);
			cout<<"\n"<<char('A'+i)<<". ";
			SetColor(_optclr,0);
			cout<<(i==p?wd.en:opt.en);
		}
		SetColor(8,0);
		cout<<"\n:";
		int ch = getch();
		if(ch == VK_ESCAPE)
		{
			SetColor(14,0);
			cout<<"\n���˳�";
			break;
		}
		if(islower(ch))
		    ch = toupper(ch);
		if((ch - 'A') == p)
		{
			++right_cnt;
			SetColor(10,0);
			cout<<"  ����ȷ\n";
		}else{
			++wrong_cnt;
			SetColor(12,0);
			cout<<"  ������\n";
			SetColor(15,0);
			cout<<"��ȷ�𰸣�"<<wd.en<<"  "<<wd.ch<<"\n";
		}
		++n;
		Sleep(30);
	}
	--n;
	if(n <= 0)
		return;
	SetColor(14,0);
	cout<<"\n__________________";
	cout<<"\n     ͳ������     ";
	cout<<"\n*  ����: ";
	SetColor(6,0);
	cout<<n<<" ";
	SetColor(10,0);
	cout<<"\n�� ��ȷ: ";
	SetColor(2,0);
	cout<<right_cnt;
	SetColor(12,0);
	cout<<"\n�� ����: ";
	SetColor(4,0);
	cout<<wrong_cnt;
	SetColor(11,0);
	cout<<"\n$  ��ȷ��: ";
	SetColor(3,0);
	float percent = float(right_cnt)/n*100;
	cout<<percent<<"%";
	SetColor(10,0);
	cout<<"\n��  ���";
	if(abs(percent - 100.0f) < 0.01f)
	{
		SetColor(10,0);
		cout<<"���񣡣�������";
	}else if(percent > 97.0f)
	{
		SetColor(10,0);
		cout<<"���У�������";
	}else if(percent > 95.0f)
	{
		SetColor(10,0);
		cout<<"��ʦ������";
	}else if(percent > 90.0f)
	{
		SetColor(11,0);
		cout<<"ţ�ˣ���";
	}else if(percent > 80.0f)
	{
		SetColor(11,0);
		cout<<"��ʿ��";
	}else if(percent > 70.0f)
	{
		SetColor(11,0);
		cout<<"����!";
	}else if(percent > 63.0f)
	{
		SetColor(14,0);
		cout<<"����.";
	}else if(percent > 55.0f)
	{
		SetColor(15,0);
		cout<<"����.";
	}else if(percent > 48.0f)
	{
		SetColor(7,0);
		cout<<"ע���.";
	}else if(percent > 36.0f)
	{
		SetColor(8,0);
		cout<<"��̫����.";
	}
	else if(percent > 28.0f)
	{
		SetColor(8,0);
		cout<<"��";
	}
	else if(percent > 17.0f)
	{
		SetColor(6,0);
		cout<<"�";
	}
	else if(percent > 10.0f)
	{
		SetColor(6,0);
		cout<<"̫����";
	}
	else if(percent > 4.0f)
	{
		SetColor(3,0);
		cout<<"��!";
	}
	else if(percent > 0.5f)
	{
		SetColor(2,0);
		cout<<"�㻹�����ٵ�һ�㣡  :)";
	}else{
		SetColor(1,0);
		cout<<"������   :(";
	}
	SetColor(14,0);
	cout<<"\n__________________";
	SetColor(15,0);
	Pause("\n>> �밴��������� <<");
	SetColor(8,0);
}
string SelectDicitonary(void)
{
	if(dicts.empty())
	{
		SetColor(12,0); 
		cout<<"\n����û��һ���ʿ�";
		exit(0);
		return "";
	}
	SetColor(14,0);
	cout<<"\n=========================";
	cout<<"\n       ѡ����Ĵʿ�      ";
	for(int i=0;i<dicts.size();++i)
	{
		SetColor(10,0);
		cout<<"\n"<<i<<":";
		SetColor(11,0);
		cout<<dicts.at(i).name<<" ";
	}
	SetColor(14,0);
	cout<<"\n=========================";
	SetColor(6,0);
	cout<<"\n> ";
	int n;
_inp:
	cin>>n;
	if(n >= dicts.size())
		goto _inp;
	return dicts.at(n).name;
}
int main()
{
	hwnd = GetConsoleWindow();
	ShowWindow(hwnd,SW_MAXIMIZE);
	if(!ReadData())
		return 0;
	//Start();
//	getch();
	//ListWords();
	srand(time(NULL));
	string name;
	name = SelectDicitonary();
	Start(name);
	return 1;
} 
