combine(char* l, char* r){
  char* res;
  int len_l, len_r;

  len_l = strlen(l);
  len_r = strlen(r);
  if(*(l+len_l-1) == '/'){
    if(*r == '/'){
      res = emalloc(len_l+len_r, "combine");
      strcpy(res, l);
      strcpy(res+len_l, r+1);
    }else{
      res = emalloc(len_l+len_r+1, "combine");
      strcpy(res, l);
      strcpy(res+len_l, r);
    }
  }else{
    if(*r == '/'){
      res = emalloc(len_l+len_r+1, "combine");
      strcpy(res, l);
      strcpy(res+len_l, r);
    }else{
      res = emalloc(len_l+len_r+2, "combine");
      strcpy(res, l);
      *(res+len_l) = '/';
      strcpy(res+len_l+1, r);
    }
  }
  return res;
}
