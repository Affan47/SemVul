randhexCmd(
  Th_Interp *interp,
  void *p,
  int argc,
  const char **argv,
  int *argl
){
  int n;
  unsigned char aRand[50];
  unsigned char zOut[100];
  if( argc!=1 && argc!=2 ){
    return Th_WrongNumArgs(interp, "repository ?BOOLEAN?");
  }
  if( argc==2 ){
    if( Th_ToInt(interp, argv[1], argl[1], &n) ){
      return TH_ERROR;
    }
    if( n<1 ) n = 1;
    if( n>sizeof(aRand) ) n = sizeof(aRand);
  }else{
    n = 10;
  }
  sqlite3_randomness(n, aRand);
  encode16(aRand, zOut, n);
  Th_SetResult(interp, (const char *)zOut, -1);
  return TH_OK;
}
