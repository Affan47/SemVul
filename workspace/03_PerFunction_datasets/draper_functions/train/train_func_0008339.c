S_SET_WEAKREFR (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    s = local_symbol_convert ((struct local_symbol *) s);
  s->sy_flags.sy_weakrefr = 1;


  if (s->sy_flags.sy_used)
    symbol_mark_used (s->sy_value.X_add_symbol);
}
