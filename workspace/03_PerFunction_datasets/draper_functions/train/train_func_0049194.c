cp_parser_assignment_expression (cp_parser* parser, bool cast_p,
				 bool decltype_p, cp_id_kind * pidk)
{
  tree expr;


  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_THROW))
    expr = cp_parser_throw_expression (parser);


  else
    {

      expr = cp_parser_binary_expression (parser, cast_p, false,
					  decltype_p,
					  PREC_NOT_OPERATOR, pidk);


      if (cp_lexer_next_token_is (parser->lexer, CPP_QUERY))
	return cp_parser_question_colon_clause (parser, expr);
      else
	{
	  location_t loc = cp_lexer_peek_token (parser->lexer)->location;


	  enum tree_code assignment_operator
	    = cp_parser_assignment_operator_opt (parser);
	  if (assignment_operator != ERROR_MARK)
	    {
	      bool non_constant_p;
	      location_t saved_input_location;


	      tree rhs = cp_parser_initializer_clause (parser, &non_constant_p);

	      if (BRACE_ENCLOSED_INITIALIZER_P (rhs))
		maybe_warn_cpp0x (CPP0X_INITIALIZER_LISTS);


	      if (cp_parser_non_integral_constant_expression (parser,
							      NIC_ASSIGNMENT))
		return error_mark_node;


	      saved_input_location = input_location;
	      input_location = loc;
	      expr = build_x_modify_expr (loc, expr,
					  assignment_operator,
					  rhs,
					  complain_flags (decltype_p));
	      input_location = saved_input_location;
	    }
	}
    }

  return expr;
}
