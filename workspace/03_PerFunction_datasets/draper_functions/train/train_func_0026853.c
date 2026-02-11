Symbol_new(x)
char *x;
{
  struct symbol *sp;

  sp = Symbol_find(x);
  if( sp==0 ){
    sp = (struct symbol *)malloc( sizeof(struct symbol) );
    MemoryCheck(sp);
    sp->name = Strsafe(x);
    sp->type = isupper(*x) ? TERMINAL : NONTERMINAL;
    sp->rule = 0;
    sp->fallback = 0;
    sp->prec = -1;
    sp->assoc = UNK;
    sp->firstset = 0;
    sp->lambda = Bo_FALSE;
    sp->destructor = 0;
    sp->datatype = 0;
    Symbol_insert(sp,sp->name);
  }
  return sp;
}
