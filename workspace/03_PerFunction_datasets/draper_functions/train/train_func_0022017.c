symbol_get_frag (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    return local_symbol_get_frag ((struct local_symbol *) s);
  return s->sy_frag;
}
