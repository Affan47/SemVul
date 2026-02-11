symbol_mark_used (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    return;
  s->sy_flags.sy_used = 1;
  if (S_IS_WEAKREFR (s))
    symbol_mark_used (s->sy_value.X_add_symbol);
}
