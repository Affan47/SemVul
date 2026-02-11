__thread_exit__key(_pthread_descr th) {
  int i;
  void (*dstr)(void*);

  for (i=0;i<PTHREAD_KEYS_MAX;++i) {
    if ((__thread_keys[i].used)&&(dstr=__thread_keys[i].destructor)) {
      void*data=th->tkd[i];
      if (data) dstr(data);
    }
  }
}
