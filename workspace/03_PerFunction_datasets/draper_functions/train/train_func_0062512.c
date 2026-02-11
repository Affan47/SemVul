readPasswd(UINT8* buff,UINT32 len)
{
	if(len==0)
		return E_SUCCESS;

#ifndef _WIN32
	termios tmpTermios;
	UINT32 flags;
	bool bRestore=true;
	if(tcgetattr(STDIN_FILENO,&tmpTermios)!=0)
		{
			bRestore=false;
		}
	flags=tmpTermios.c_lflag;
	tmpTermios.c_lflag&=~(ECHO);
	if(bRestore)
		tcsetattr(STDIN_FILENO,TCSAFLUSH,&tmpTermios);
#endif

	UINT32 i=0;
	for(i=0;i<len-1;i++)
		{
#ifdef _WIN32
			int c=::getch();
#else
			int c=getchar();
#endif
			if(c<=0||c=='\r'||c=='\n')
				break;
			buff[i]=c;
		}
	buff[i]=0;

#ifndef _WIN32
	tmpTermios.c_lflag=flags;
	if(bRestore)
		tcsetattr(STDIN_FILENO,TCSAFLUSH,&tmpTermios);
#endif
	return E_SUCCESS;
}
