yyerror(s)
char *s;
{ char modmsg[1000];
  if ( help_flag ) return 0;
  parens = brace_depth = in_quote = 0;
  strncpy(modmsg,s,998);
  if ( modmsg[strlen(modmsg)-1] != '\n' )
    strcat(modmsg,"\n");
  if ( datafile_flag )
   {
     if ( listtop == 2 ) return 0;
     kb_error(2407,modmsg,PARSE_ERROR);
   }
  else
    {
      kb_error(2408,modmsg,SYNTAX_ERROR);
    }
  return 0;
}
