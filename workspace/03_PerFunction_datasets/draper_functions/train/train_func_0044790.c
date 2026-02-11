regexpCmd(
  Th_Interp *interp,
  void *p,
  int argc,
  const char **argv,
  int *argl
){
  int rc;
  int noCase = 0;
  int nArg = 1;
  ReCompiled *pRe = 0;
  const char *zErr;
  if( argc<3 || argc>5 ){
    return Th_WrongNumArgs(interp, REGEXP_WRONGNUMARGS);
  }
  if( fossil_strcmp(argv[nArg], "-nocase")==0 ){
    noCase = 1; nArg++;
  }
  if( fossil_strcmp(argv[nArg], "--")==0 ) nArg++;
  if( nArg+2!=argc ){
    return Th_WrongNumArgs(interp, REGEXP_WRONGNUMARGS);
  }
  zErr = re_compile(&pRe, argv[nArg], noCase);
  if( !zErr ){
    Th_SetResultInt(interp, re_match(pRe,
        (const unsigned char *)argv[nArg+1], argl[nArg+1]));
    rc = TH_OK;
  }else{
    Th_SetResult(interp, zErr, -1);
    rc = TH_ERROR;
  }
  re_free(pRe);
  return rc;
}
