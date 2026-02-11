cmp_nouns(const void *a,const void *b)

{
  word wa,wb;
  int cmp;

  wa=getword(*((const int*)a),1);
  wb=getword(*((const int*)b),1);
  cmp=strcmp(dict[wa],dict[wb]);
  if (cmp!=0) return cmp;
  wa=getword(*(const int*)a,2);
  wb=getword(*(const int*)b,2);
  return strcmp(dict[wa],dict[wb]);
}
