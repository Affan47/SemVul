cp_parser_explicit_specialization (cp_parser* parser)
{

  cp_parser_require_keyword (parser, RID_TEMPLATE, "`template'");

  cp_parser_require (parser, CPP_LESS, "`<'");

  cp_parser_require (parser, CPP_GREATER, "`>'");

  ++parser->num_template_parameter_lists;

  begin_specialization ();


  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_TEMPLATE))
    {
      if (cp_lexer_peek_nth_token (parser->lexer, 2)->type == CPP_LESS
	  && cp_lexer_peek_nth_token (parser->lexer, 3)->type != CPP_GREATER)
	cp_parser_template_declaration_after_export (parser,
						     false);
      else
	cp_parser_explicit_specialization (parser);
    }
  else

    cp_parser_single_declaration (parser,
				  false,
				  NULL);


  end_specialization ();

  --parser->num_template_parameter_lists;
}
