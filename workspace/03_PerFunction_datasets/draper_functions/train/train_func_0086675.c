strCompare(const void *pKey1, int n1, const void *pKey2, int n2){
  if( n1!=n2 ) return n2-n1;
  return sqliteStrNICmp((const char*)pKey1,(const char*)pKey2,n1);
}
