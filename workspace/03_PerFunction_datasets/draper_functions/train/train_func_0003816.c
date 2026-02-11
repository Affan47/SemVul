cp_parser_assignment_expression (cp_parser* parser)
{
  tree expr;


  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_THROW))
    expr = cp_parser_throw_expression (parser);


  else
    {

      expr = cp_parser_logical_or_expression (parser);


      if (cp_lexer_next_token_is (parser->lexer, CPP_QUERY))
	return cp_parser_question_colon_clause (parser, expr);
      else
	{
	  enum tree_code assignment_operator;


	  assignment_operator
	    = cp_parser_assignment_operator_opt (parser);
	  if (assignment_operator != ERROR_MARK)
	    {
	      tree rhs;


	      rhs = cp_parser_assignment_expression (parser);


	      if (cp_parser_non_integral_constant_expression (parser,
							      "an assignment"))
		return error_mark_node;

	      expr = build_x_modify_expr (expr,
					  assignment_operator,
					  rhs);
	    }
	}
    }

  return expr;
}
