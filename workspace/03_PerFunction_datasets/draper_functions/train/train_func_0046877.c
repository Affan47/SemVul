cp_parser_block_declaration (cp_parser *parser,
			     bool      statement_p)
{
  cp_token *token1;
  int saved_pedantic;


  if (cp_parser_extension_opt (parser, &saved_pedantic))
    {

      cp_parser_block_declaration (parser, statement_p);

      pedantic = saved_pedantic;

      return;
    }


  token1 = cp_lexer_peek_token (parser->lexer);


  if (token1->keyword == RID_ASM)
    {
      if (statement_p)
	cp_parser_commit_to_tentative_parse (parser);
      cp_parser_asm_definition (parser);
    }


  else if (token1->keyword == RID_NAMESPACE)
    cp_parser_namespace_alias_definition (parser);


  else if (token1->keyword == RID_USING)
    {
      cp_token *token2;

      if (statement_p)
	cp_parser_commit_to_tentative_parse (parser);


      token2 = cp_lexer_peek_nth_token (parser->lexer, 2);
      if (token2->keyword == RID_NAMESPACE)
	cp_parser_using_directive (parser);


      else if (cxx_dialect >= cxx0x
	       && token2->type == CPP_NAME
	       && ((cp_lexer_peek_nth_token (parser->lexer, 3)->type == CPP_EQ)
		   || (cp_lexer_peek_nth_token (parser->lexer, 3)->keyword
		       == RID_ATTRIBUTE)))
	cp_parser_alias_declaration (parser);

      else
	cp_parser_using_declaration (parser,
				     false);
    }


  else if (token1->keyword == RID_LABEL)
    {
      cp_lexer_consume_token (parser->lexer);
      error_at (token1->location, "%<__label__%> not at the beginning of a block");
      cp_parser_skip_to_end_of_statement (parser);

      if (cp_lexer_next_token_is (parser->lexer, CPP_SEMICOLON))
	cp_lexer_consume_token (parser->lexer);
    }

  else if (token1->keyword == RID_STATIC_ASSERT)
    cp_parser_static_assert (parser, false);

  else
    cp_parser_simple_declaration (parser, !statement_p,
				  NULL);
}
