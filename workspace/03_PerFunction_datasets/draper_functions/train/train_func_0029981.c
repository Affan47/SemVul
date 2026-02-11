symbol_get_tc (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    s = local_symbol_convert ((struct local_symbol *) s);
  return &s->sy_tc;
}
