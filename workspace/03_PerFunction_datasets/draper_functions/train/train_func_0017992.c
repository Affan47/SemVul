is_symbol(int symnum, char *str, int arity)
{
  Symbol n = lookup_by_id(symnum);
  if (n == NULL)
    return FALSE;
  else
    return (n->arity == arity && str_ident(n->name, str));
}
