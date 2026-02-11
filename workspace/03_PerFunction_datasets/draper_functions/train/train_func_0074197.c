lexch(l)
  struct lex *l;
{
  int ch=EOF;

  if(l->size) {
    ch=*l->base;
    ++l->base;
    --l->size;
  }

  return ch;
}
