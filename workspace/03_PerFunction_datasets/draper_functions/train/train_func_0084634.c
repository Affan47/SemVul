ReadConfig (char *ScriptName)
{
  extern FILE *yyin;
  char s[FILENAME_MAX];


  sprintf(s,"%s%s%s",ScriptPath,(!*ScriptPath ? "" : "/"),ScriptName);
  yyin = fopen(s,"r");
  if (yyin == NULL) {
    TryToFind(ScriptName);
  }
  if (yyin == NULL)
  {
    fprintf(stderr,"[%s][ReadConfig]: <<ERROR>> Can't open the script %s\n",
	    module->name,s);
    exit(1);
  }


  yyparse();


  fclose(yyin);
}
