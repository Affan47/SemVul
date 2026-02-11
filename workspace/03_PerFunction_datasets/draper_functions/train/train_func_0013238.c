vacuumCallback1(void *pArg, int argc, char **argv, char **NotUsed){
  vacuumStruct *p = (vacuumStruct*)pArg;
  int rc = 0;
  assert( argc==3 );
  if( argv==0 ) return 0;
  assert( argv[0]!=0 );
  assert( argv[1]!=0 );
  assert( argv[2]!=0 );
  rc = execsql(p->pzErrMsg, p->dbNew, argv[2]);
  if( rc==SQLITE_OK && strcmp(argv[0],"table")==0 ){
    char *zErrMsg = 0;
    p->s1.nUsed = 0;
    appendText(&p->s1, "SELECT * FROM ", -1);
    appendQuoted(&p->s1, argv[1]);
    p->zTable = argv[1];
    rc = sqlite_exec(p->dbOld, p->s1.z, vacuumCallback2, p, &zErrMsg);
    if( zErrMsg ){
      sqliteSetString(p->pzErrMsg, zErrMsg, (char*)0);
      sqlite_freemem(zErrMsg);
    }
  }
  if( rc!=SQLITE_ABORT ) p->rc = rc;
  return rc;
}
