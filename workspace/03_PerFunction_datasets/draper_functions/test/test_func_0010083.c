symbol_set_frag (symbolS *s, fragS *f)
{
  if (LOCAL_SYMBOL_CHECK (s))
    {
      local_symbol_set_frag ((struct local_symbol *) s, f);
      return;
    }
  s->sy_frag = f;
  S_CLEAR_WEAKREFR (s);
}
