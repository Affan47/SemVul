symbol_clear_used (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    s = local_symbol_convert ((struct local_symbol *) s);
  s->sy_flags.sy_used = 0;
}
