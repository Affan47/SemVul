stralloc_ready(stralloc *sa,size_t len) {
  register size_t wanted=len+(len>>3)+30;
  if (!sa->s || sa->a<len) {
    register char* tmp;
    if (!(tmp=realloc(sa->s,wanted)))
      return 0;
    sa->a=wanted;
    sa->s=tmp;
  }
  return 1;
}
