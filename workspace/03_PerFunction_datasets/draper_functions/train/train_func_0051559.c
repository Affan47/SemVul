list_options(FILE *fd)
#else
list_options(fd)
     FILE *fd;
#endif
{
	unsigned i;


	(void)fprintf(fd,"\n%s",COPYRIGHT_DATE);
	(void)fprintf(fd,"\n%s\n",COPYRIGHT_NOTICE);


	(void)fprintf(fd,"\nCommandline options [default]:");
	for(i=0; i<NUM_SWITCHES; i++) {

	  if( !debug_latest &&
	     strncmp(switchopt[i].explanation,"debug",5) == 0)
	    continue;

	  (void)fprintf(fd,"\n    %c[no]%s",OPT_PREFIX,switchopt[i].name);
	  (void)fprintf(fd," [%s]",*(switchopt[i].switchflag)? "yes": "no");
	  (void)fprintf(fd,": %s",switchopt[i].explanation);
	}

	for(i=0; i<NUM_STRSETTINGS; i++) {
	  if( !debug_latest &&
	     strncmp(strsetting[i].explanation,"debug",5) == 0)
	    continue;

	  (void)fprintf(fd,"\n    %c%s=str ",OPT_PREFIX,strsetting[i].name);


	  (void)fprintf(fd,"[%s]",
		*(strsetting[i].strvalue)?
			*(strsetting[i].strvalue):
			strsetting[i].option_list != (WarnOptionList *)NULL?
			   strsetting[i].option_list[0].name:
			   "NONE");
	  (void)fprintf(fd,": %s",strsetting[i].explanation);
	  if( strsetting[i].option_list != (WarnOptionList *)NULL )
	    (void)fprintf(fd,"\n        Use %c%s=help for list of options",
#ifdef OPTION_PREFIX_SLASH
			  '/',
#else
			  '-',
#endif
			  strsetting[i].name);
	}

	(void)fprintf(fd,"\nSettings (legal range) [default]:");
	for(i=0; i<NUM_SETTINGS; i++) {

	  if( !debug_latest &&
	     strncmp(setting[i].explanation,"debug",5) == 0)
	    continue;

	  (void)fprintf(fd,"\n    %c%s=dd ",OPT_PREFIX,setting[i].name);
	  (void)fprintf(fd,"(%d to %d) ",setting[i].minlimit,
		  setting[i].maxlimit);
	  (void)fprintf(fd,"[%d]",*(setting[i].setvalue));
	  (void)fprintf(fd,": %s",setting[i].explanation);
	}

    (void)fprintf(fd,
	"\n(First %d chars of option name significant)\n",OPT_MATCH_LEN);
}
