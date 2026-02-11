calldriver(void)
{
	L9BYTE* a6=list9startptr;
	int d0=*a6++;
#ifdef CODEFOLLOW
	fprintf(f," %s",drivercalls[d0]);
#endif

	if (d0==0x16 || d0==0x17)
	{
		int d1=*a6;
		if (d1>0xfa) *a6=1;
		else if (d1+1>=RAMSAVESLOTS) *a6=0xff;
		else
		{
			*a6=0;
			if (d0==0x16) ramsave(d1+1); else ramload(d1+1);
		}
		*list9startptr=*a6;
	}
	else if (d0==0x0b)
	{
		char NewName[MAX_PATH];
		strcpy(NewName,LastGame);
		if (*a6==0)
		{
			printstring("\rSearching for next sub-game file.\r");
			if (!os_get_game_file(NewName,MAX_PATH))
			{
				printstring("\rFailed to load game.\r");
				return;
			}
		}
		else
		{
			os_set_filenumber(NewName,MAX_PATH,*a6);
		}
		LoadGame2(NewName,NULL);
	}
	else driver(d0,a6);
}
