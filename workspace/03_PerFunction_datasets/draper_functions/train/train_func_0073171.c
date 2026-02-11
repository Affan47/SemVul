user_match(const char *s,int n) {
  Fnlst *f;
  for (f=my_fnlst;f<my_fnlst+NF;f++){
     if (f->s && !strncmp(s,f->s,n)) {
        my_load(f->fn,f->s);
        return 1;
     }
  }
  return 0;
}
