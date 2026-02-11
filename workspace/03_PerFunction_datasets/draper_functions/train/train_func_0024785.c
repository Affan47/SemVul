create_cmd_mpqc(G_CONST_RETURN gchar* command, gboolean local, gchar* cmddir, gchar* cmdfile, gchar* cmdall)
{
        FILE* fcmd = NULL;
#ifndef G_OS_WIN32
	gchar buffer[BSIZE];
#endif

	if(local)
  		sprintf(cmddir,"%s", fileopen.localdir);
	else
		sprintf(cmddir,"%s%stmp", gabedit_directory(), G_DIR_SEPARATOR_S);

#ifndef G_OS_WIN32
	sprintf(cmdfile,"%s.cmd", fileopen.projectname);
#else
	if(!local)
		sprintf(cmdfile,"%s.cmd", fileopen.projectname);
	else
		sprintf(cmdfile,"%s.bat", fileopen.projectname);
#endif
  	sprintf(cmdall,"%s%s%s",cmddir,G_DIR_SEPARATOR_S,cmdfile);


  	fcmd = FOpen(cmdall, "w");
	if(!fcmd)
	{
		if(local)
  			Message(_("\nI can not create cmd file\n"),_("Error"),TRUE);
		return FALSE;
	}

	if(local)
	{
#ifdef G_OS_WIN32
		addUnitDisk(fcmd, fileopen.localdir);
#endif
		fprintf(fcmd,"cd %s\n", fileopen.localdir);
	}
	else
		fprintf(fcmd,"cd %s\n", fileopen.remotedir);


#ifndef G_OS_WIN32
	fprintf(fcmd,"%s %s > %s &\n",command,fileopen.datafile, fileopen.outputfile);
	fprintf(fcmd,"exit\n");
#else
	 if(!local)
	 {
		 fprintf(fcmd,"%s %s > %s &\n",command,fileopen.datafile, fileopen.outputfile);
		 fprintf(fcmd,"exit\n");
	 }
	 else
		 fprintf(fcmd,"%s %s > %s\n",command,fileopen.datafile, fileopen.outputfile);

#endif
	fclose(fcmd);
#ifndef G_OS_WIN32
  	sprintf(buffer,"chmod u+x %s",cmdall);
	{ int i = system(buffer);}
#endif
	return TRUE;
}
