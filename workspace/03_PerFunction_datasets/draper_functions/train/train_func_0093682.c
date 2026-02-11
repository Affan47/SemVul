cmd_help()
{
	FILE	*f;
	char	*s, helpfile[256];

	sprintf(helpfile,"%s/%s",Grufti->admindir,Grufti->helpfile);
	if((f = fopen(helpfile,"r")) == NULL)
	{
		say("No helpfile.");
		Log_write(LOG_MAIN | LOG_ERROR,"*","No helpfile was found. (req'd by %s %s)",cmdinfo.from_n,cmdinfo.from_uh);
		return;
	}

	context;
	if(!cmdinfo.isparam)
	{
		find_topic(f,"standard");
		while((s = get_ftext(f)))
			say(s);
	}
	else
	{
		if(!find_topic(f,cmdinfo.tok1))
			sayf(0,0,"No help available for \"%s\".",cmdinfo.tok1);
		else
			while((s = get_ftext(f)))
				say(s);
	}

	context;
	fclose(f);
}
