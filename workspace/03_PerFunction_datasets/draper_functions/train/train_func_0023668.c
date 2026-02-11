mergehints(CBMAP *total, CBMAP *local){
  static pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
  const char *kbuf, *vbuf;
  char numbuf[NUMBUFSIZ];
  int ksiz, num, vsiz;
  if(pthread_mutex_lock(&mymutex) != 0) return;
  cbmapiterinit(local);
  while((kbuf = cbmapiternext(local, &ksiz)) != NULL){
    num = atoi(cbmapiterval(kbuf, NULL));
    if((vbuf = cbmapget(total, kbuf, ksiz, NULL)) != NULL) num += atoi(vbuf);
    vsiz = sprintf(numbuf, "%d", num);
    cbmapput(total, kbuf, ksiz,  numbuf, vsiz, TRUE);
  }
  pthread_mutex_unlock(&mymutex);
}
