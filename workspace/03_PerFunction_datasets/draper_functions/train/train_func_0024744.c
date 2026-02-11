warn_of_redefinition (pfile, node, macro2)
     cpp_reader *pfile;
     const cpp_hashnode *node;
     const cpp_macro *macro2;
{
  const cpp_macro *macro1;
  unsigned int i;


  if (node->flags & NODE_WARN)
    return true;


  macro1 = node->value.macro;


  if (macro1->paramc != macro2->paramc
      || macro1->fun_like != macro2->fun_like
      || macro1->variadic != macro2->variadic)
    return true;


  for (i = 0; i < macro1->paramc; i++)
    if (macro1->params[i] != macro2->params[i])
      return true;


  if (CPP_OPTION (pfile, traditional))
    return _cpp_expansions_different_trad (macro1, macro2);

  if (macro1->count != macro2->count)
    return true;

  for (i = 0; i < macro1->count; i++)
    if (!_cpp_equiv_tokens (&macro1->exp.tokens[i], &macro2->exp.tokens[i]))
      return true;

  return false;
}
