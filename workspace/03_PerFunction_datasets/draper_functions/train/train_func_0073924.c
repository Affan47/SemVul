anthy_xstr_dup(xstr *s)
{
  int i;
  xstr *x = (xstr *)malloc(sizeof(xstr));
  x->len = s->len;
  if (s->len) {
    x->str = malloc(sizeof(xchar)*s->len);
  }else{
    x->str = NULL;
  }
  for (i = 0; i < x->len; i++) {
    x->str[i] = s->str[i];
  }
  return x;
}
