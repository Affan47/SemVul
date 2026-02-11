sqlitepager_opentemp(char *zFile, OsFile *fd){
  int cnt = 8;
  int rc;
  do{
    cnt--;
    sqliteOsTempFileName(zFile);
    rc = sqliteOsOpenExclusive(zFile, fd, 1);
  }while( cnt>0 && rc!=SQLITE_OK );
  return rc;
}
