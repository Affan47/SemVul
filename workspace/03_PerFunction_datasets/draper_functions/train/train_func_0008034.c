cp_parser_omp_clause_collapse (cp_parser *parser, tree list, location_t location)
{
  tree c, num;
  location_t loc;
  HOST_WIDE_INT n;

  loc = cp_lexer_peek_token (parser->lexer)->location;
  if (!cp_parser_require (parser, CPP_OPEN_PAREN, RT_OPEN_PAREN))
    return list;

  num = cp_parser_constant_expression (parser, false, NULL);

  if (!cp_parser_require (parser, CPP_CLOSE_PAREN, RT_CLOSE_PAREN))
    cp_parser_skip_to_closing_parenthesis (parser, true,
					   false,
					   true);

  if (num == error_mark_node)
    return list;
  num = fold_non_dependent_expr (num);
  if (!INTEGRAL_TYPE_P (TREE_TYPE (num))
      || !host_integerp (num, 0)
      || (n = tree_low_cst (num, 0)) <= 0
      || (int) n != n)
    {
      error_at (loc, "collapse argument needs positive constant integer expression");
      return list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse", location);
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_COLLAPSE_EXPR (c) = num;

  return c;
}
