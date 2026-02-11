cp_parser_skip_to_end_of_statement (cp_parser* parser)
{
  unsigned nesting_depth = 0;

  while (true)
    {
      cp_token *token;


      token = cp_lexer_peek_token (parser->lexer);

      if (token->type == CPP_EOF)
	break;


      if (token->type == CPP_SEMICOLON && !nesting_depth)
	break;


      if (token->type == CPP_CLOSE_BRACE)
	{


	  if (nesting_depth == 0)
	    break;


	  if (--nesting_depth == 0)
	    {
	      cp_lexer_consume_token (parser->lexer);
	      break;
	    }
	}


      else if (token->type == CPP_OPEN_BRACE)
	++nesting_depth;

      cp_lexer_consume_token (parser->lexer);
    }
}
