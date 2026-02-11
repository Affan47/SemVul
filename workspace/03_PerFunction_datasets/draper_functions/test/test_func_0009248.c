add_cache(char *number, TELNUM *num) {
  int i, mlru,m;
  mlru=9999;
  m=0;
  for (i=0; i<CACHE_SIZE; i++) {
    if(!*num_cache[i].number) {
      Strncpy(num_cache[i].number, number, TN_MAX_NUM_LEN);
      memcpy(&num_cache[i].num, num, sizeof(TELNUM));
      break;
    }
    if(num_cache[i].lru<mlru) {
      m=i;
      mlru=num_cache[i].lru;
    }
  }
  if(i==CACHE_SIZE) {
    Strncpy(num_cache[m].number, number, TN_MAX_NUM_LEN);
    memcpy(&num_cache[m].num, num, sizeof(TELNUM));
    num_cache[m].lru=1;
  }
}
