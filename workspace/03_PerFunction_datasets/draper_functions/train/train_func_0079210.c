genfkeyCmdCb(void *pCtx, int eType, const char *z){
  GenfkeyCmd *p = (GenfkeyCmd *)pCtx;
  if( eType==GENFKEY_ERROR && !p->isIgnoreErrors ){
    p->nErr++;
    fprintf(stderr, "%s\n", z);
  }

  if( p->nErr==0 && (
        (eType==GENFKEY_CREATETRIGGER)
     || (eType==GENFKEY_DROPTRIGGER && !p->isNoDrop)
  )){
    if( p->isExec ){
      sqlite3_exec(p->db, z, 0, 0, 0);
    }else{
      char *zCol = "sql";
      callback((void *)p->pCb, 1, (char **)&z, (char **)&zCol);
    }
  }

  return SQLITE_OK;
}
