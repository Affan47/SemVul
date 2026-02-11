function_or_relation_sn(char *str)
{
  int i;
  for (i = 0; i < SYM_TAB_SIZE; i++) {
    Plist p;
    for (p = By_id[i]; p; p = p->next) {
      Symbol s = p->v;
      if ((s->type == FUNCTION_SYMBOL || s->type == PREDICATE_SYMBOL) &&
	  str_ident(str, s->name))
	return s->symnum;
    }
  }
  return -1;
}
