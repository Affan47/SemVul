lexmatch(l, type, state, t)
  struct lex *l;
  struct string *t;
{
  if(l->type==type) {
    l->state=state;

    if(t) {
      strcopy(t, &l->la);
      if(!strdeepen(t)) {
        l->type=0;
        l->error|=1;
        return 0;
      }
      if(!strappend0(t)) {
        l->type=0;
        l->error|=1;
        return 0;
      }
    }

    lexnext(l);
    return 1;
  } else {
    l->expect=type;
  }

  return 0;
}
