getFunctionValueFromString(const char * string, const char * x, double xValue)
{
  CoinYacc info;
  double unset = -1.23456787654321e-97;
  info.length=0;
  info.symtable=NULL;
  info.symbuf=NULL;
  init_table ( info.symtable);
  info.unsetValue=unset;
  int error=0;

  double associated[2];
  associated[0]=xValue;
  associated[1]=unset;

  CoinModelHash stringX;
  addString(stringX,x);
  addString(stringX,string);


  int yychar;


  YYSTYPE yylval;


  int yynerrs;

  double value = yyparse ( info.symtable, string,info.symbuf,info.length,
                           associated,stringX,error,info.unsetValue,
                           yychar, yylval,  yynerrs);

  int logLevel_=2;
  if (error){


    if (logLevel_>=1)
    printf("string %s returns value %g and error-code %d\n",
	   string,value,error);
    value = unset;
  } else if (logLevel_>=2) {
    printf("%s computes as %g\n",string,value);
  }
  freesym( info.symtable);
  free(info.symbuf);
  return value;
}
