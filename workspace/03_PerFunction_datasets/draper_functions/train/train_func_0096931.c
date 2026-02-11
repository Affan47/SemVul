stralloc_starts(stralloc *sa,const char *in) {
  register size_t len=str_len(in);
  return (len<=sa->len && !byte_diff(sa->s,len,in));
}
