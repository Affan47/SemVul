symbol_set_value_expression (symbolS *s, const expressionS *exp)
{
  if (LOCAL_SYMBOL_CHECK (s))
    s = local_symbol_convert ((struct local_symbol *) s);
  s->sy_value = *exp;
  S_CLEAR_WEAKREFR (s);
}
