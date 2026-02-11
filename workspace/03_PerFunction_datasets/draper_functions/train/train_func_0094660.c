findNamedArg(const char *b,int l)
{
  char *s;
  int i;

  for (i=0;;i++) {
    s=C->namedargs[i];
    if (s==NULL) return -1;
    if (idequal(b,l,s)) return i;
  }
}
