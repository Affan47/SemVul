cp_parser_omp_critical (cp_parser *parser, cp_token *pragma_tok)
{
  tree stmt, name = NULL;

  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_PAREN))
    {
      cp_lexer_consume_token (parser->lexer);

      name = cp_parser_identifier (parser);

      if (name == error_mark_node
	  || !cp_parser_require (parser, CPP_CLOSE_PAREN, RT_CLOSE_PAREN))
	cp_parser_skip_to_closing_parenthesis (parser, true,
					       false,
					       true);
      if (name == error_mark_node)
	name = NULL;
    }
  cp_parser_require_pragma_eol (parser, pragma_tok);

  stmt = cp_parser_omp_structured_block (parser);
  return c_finish_omp_critical (input_location, stmt, name);
}
