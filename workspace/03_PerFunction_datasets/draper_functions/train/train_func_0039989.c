end_of_commands_term(Term t)
{
  if (t == NULL)
    return FALSE;
  else if (!CONSTANT(t))
    return FALSE;
  else
    return is_symbol(SYMNUM(t), "end_of_commands", 0);
}
