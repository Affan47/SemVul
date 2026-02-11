create_cmd_psicode(G_CONST_RETURN gchar* command, gboolean local, gchar* cmddir, gchar* cmdfile, gchar* cmdall)
{
        FILE* fcmd = NULL;
	gchar* commandStr = g_strdup(command);
#ifndef G_OS_WIN32
	gchar buffer[BSIZE];
#endif
	delete_last_spaces(commandStr);
	delete_first_spaces(commandStr);

	if(local)
  		sprintf(cmddir,"%s", fileopen.localdir);
	else
		sprintf(cmddir,"%s%stmp", gabedit_directory(), G_DIR_SEPARATOR_S);

#ifndef G_OS_WIN32
	sprintf(cmdfile,"%s.cmd", fileopen.projectname);
#else
	if(!local) sprintf(cmdfile,"%s.cmd", fileopen.projectname);
	else sprintf(cmdfile,"%s.bat", fileopen.projectname);
#endif
  	sprintf(cmdall,"%s%s%s",cmddir,G_DIR_SEPARATOR_S,cmdfile);

  	fcmd = FOpen(cmdall, "w");
	if(!fcmd)
	{
		if(local) Message(_("\nI can not create cmd file\n"),_("Error"),TRUE);
		return FALSE;
	}
#ifndef G_OS_WIN32
	fprintf(fcmd,"#!/bin/sh\n");
#else
	if(local)
	{
		if(strstr(psicodeDirectory,"\"")) fprintf(fcmd,"set PATH=%s;%cPATH%c\n",psicodeDirectory,'%','%');
		else fprintf(fcmd,"set PATH=\"%s\";%cPATH%c\n",psicodeDirectory,'%','%');
	}
#endif

	if(local)
	{
#ifdef G_OS_WIN32
		addUnitDisk(fcmd, fileopen.localdir);
#endif
		fprintf(fcmd,"cd %s\n", fileopen.localdir);
	}
	else fprintf(fcmd,"cd %s\n", fileopen.remotedir);


	if(!strcmp(commandStr,"psi4") || !strcmp(commandStr,"nohup psi4"))
	{
#ifdef G_OS_WIN32
		fprintf(fcmd,"del %s.db\n",fileopen.projectname);
#else
		fprintf(fcmd,"rm -f %s.db\n",fileopen.projectname);
#endif
		fprintf(fcmd,"%s -i %s -o %s.out &\n",command,fileopen.datafile,fileopen.projectname);
		fprintf(fcmd,"exit\n");
	}
	else
	{
		 fprintf(fcmd,"%s %s &\n",command,fileopen.datafile);
		 fprintf(fcmd,"exit\n");
	}
	fclose(fcmd);
#ifndef G_OS_WIN32
  	sprintf(buffer,"chmod u+x %s",cmdall);
	{ int i = system(buffer);}
#endif
	if(commandStr) g_free(commandStr);
	return TRUE;
}
