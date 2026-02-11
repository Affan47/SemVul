sqliteStrDup(const char *z){
  char *zNew;
  if( z==0 ) return 0;
  zNew = sqliteMallocRaw(strlen(z)+1);
  if( zNew ) strcpy(zNew, z);
  return zNew;
}
