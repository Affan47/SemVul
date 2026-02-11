namespace_ancestor (tree ns1, tree ns2)
{
  timevar_push (TV_NAME_LOOKUP);
  if (is_ancestor (ns1, ns2))
    POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, ns1);
  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP,
                          namespace_ancestor (CP_DECL_CONTEXT (ns1), ns2));
}
