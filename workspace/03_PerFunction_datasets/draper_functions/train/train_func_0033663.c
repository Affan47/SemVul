iocparse(char *file)
{
  extern FILE *yyin;
  if ((yyin = fopen(file,"r")) != NULL) {
  yyparse();
  fclose(yyin);
 }
  else
 {
   printf("error : ioc file not present\n");
   exit(1);
 }
  return pt_list;
}
