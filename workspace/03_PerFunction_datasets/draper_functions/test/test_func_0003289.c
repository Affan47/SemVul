lex_compare_arity_0123(Symbol s1, Symbol s2)
{
  Ordertype base = lex_compare_base(s1, s2);

  if (base != NOT_COMPARABLE)
    return base;
  else

    return s1->arity < s2->arity ? LESS_THAN : GREATER_THAN;
}
