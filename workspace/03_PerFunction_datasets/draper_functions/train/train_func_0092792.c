cp_parser_range_for (cp_parser *parser, tree scope, tree init, tree range_decl)
{
  tree stmt, range_expr;

  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_BRACE))
    {
      bool expr_non_constant_p;
      range_expr = cp_parser_braced_list (parser, &expr_non_constant_p);
    }
  else
    range_expr = cp_parser_expression (parser, false, NULL);


  if (processing_template_decl)
    {
      if (check_for_bare_parameter_packs (range_expr))
	range_expr = error_mark_node;
      stmt = begin_range_for_stmt (scope, init);
      finish_range_for_decl (stmt, range_decl, range_expr);
      if (range_expr != error_mark_node
	  && !type_dependent_expression_p (range_expr)

	  && COMPLETE_TYPE_P (TREE_TYPE (range_expr))

	  && !BRACE_ENCLOSED_INITIALIZER_P (range_expr))
	do_range_for_auto_deduction (range_decl, range_expr);
    }
  else
    {
      stmt = begin_for_stmt (scope, init);
      stmt = cp_convert_range_for (stmt, range_decl, range_expr);
    }
  return stmt;
}
