hasfeatureCmd(
  Th_Interp *interp,
  void *p,
  int argc,
  const char **argv,
  int *argl
){
  int rc = 0;
  char const * zArg;
  if( argc!=2 ){
    return Th_WrongNumArgs(interp, "hasfeature STRING");
  }
  zArg = (char const*)argv[1];
  if(NULL==zArg){

  }
#if defined(FOSSIL_ENABLE_SSL)
  else if( 0 == fossil_strnicmp( zArg, "ssl", 3 ) ){
    rc = 1;
  }
#endif
#if defined(FOSSIL_ENABLE_TCL)
  else if( 0 == fossil_strnicmp( zArg, "tcl", 3 ) ){
    rc = 1;
  }
#endif
#if defined(FOSSIL_ENABLE_TCL_STUBS)
  else if( 0 == fossil_strnicmp( zArg, "tclStubs", 8 ) ){
    rc = 1;
  }
#endif
#if defined(FOSSIL_ENABLE_JSON)
  else if( 0 == fossil_strnicmp( zArg, "json", 4 ) ){
    rc = 1;
  }
#endif
  else if( 0 == fossil_strnicmp( zArg, "markdown", 8 ) ){
    rc = 1;
  }
  if( g.thTrace ){
    Th_Trace("[hasfeature %#h] => %d<br />\n", argl[1], zArg, rc);
  }
  Th_SetResultInt(interp, rc);
  return TH_OK;
}
