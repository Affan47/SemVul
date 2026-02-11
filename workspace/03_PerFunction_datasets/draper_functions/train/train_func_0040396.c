c_expr_to_decl (tree expr, bool *tc ATTRIBUTE_UNUSED, bool *se)
{
  if (TREE_CODE (expr) == COMPOUND_LITERAL_EXPR)
    {
      tree decl = COMPOUND_LITERAL_EXPR_DECL (expr);


      if (!TREE_STATIC (decl))
	*se = true;
      return decl;
    }
  else
    return expr;
}
