cp_parser_optional_template_keyword (cp_parser *parser)
{
  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_TEMPLATE))
    {


      if (!processing_template_decl)
	{
	  error ("`template' (as a disambiguator) is only allowed "
		 "within templates");


	  cp_lexer_purge_token (parser->lexer);
	  return false;
	}
      else
	{

	  cp_lexer_consume_token (parser->lexer);
	  return true;
	}
    }

  return false;
}
