symbol_equated_p (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    return 0;
  return s->sy_value.X_op == O_symbol;
}
