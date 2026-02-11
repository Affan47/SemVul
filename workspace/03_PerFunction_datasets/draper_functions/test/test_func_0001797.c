cp_parser_expression (cp_parser* parser)
{
  tree expression = NULL_TREE;

  while (true)
    {
      tree assignment_expression;


      assignment_expression
	= cp_parser_assignment_expression (parser);


      if (!expression)
	expression = assignment_expression;
      else
	expression = build_x_compound_expr (expression,
					    assignment_expression);


      if (cp_lexer_next_token_is_not (parser->lexer, CPP_COMMA))
	break;

      cp_lexer_consume_token (parser->lexer);

      if (cp_parser_non_integral_constant_expression (parser,
						      "a comma operator"))
	expression = error_mark_node;
    }

  return expression;
}
