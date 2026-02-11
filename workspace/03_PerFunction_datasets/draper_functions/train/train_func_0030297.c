expand(
  char *expr,
  const char *pat,
  int l
) {
  int  el = 0;
  char last = '.';
  int  i;
  for (i=0; i<l; i++) {
    char c = pat[i];
    if ( (last<'0' || last>'9')
      && (c   <'0' || c   >'9')
      ) {
      expr[el++] = '0';
    }
    expr[el++] = c;
    last = c;
  }
  if (last<'0' || last>'9') expr[el++] = '0';
  expr[el]=0;
}
