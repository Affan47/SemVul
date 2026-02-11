Hash(const char *z, int n){
  int h = 0;
  if( n<=0 ){
    n = strlen(z);
  }
  while( n-- ){
    h = h ^ (h<<5) ^ *z++;
  }
  return h & 0x7fffffff;
}
