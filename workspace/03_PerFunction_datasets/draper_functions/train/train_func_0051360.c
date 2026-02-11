c_parser_skip_to_end_of_parameter (c_parser *parser)
{
  unsigned nesting_depth = 0;

  while (true)
    {
      c_token *token = c_parser_peek_token (parser);
      if ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_depth)
	break;

      if (token->type == CPP_EOF)
	return;
      if (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	return;
      if (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      else if (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  if (nesting_depth-- == 0)
	    break;
	}

      c_parser_consume_token (parser);
    }
  parser->error = false;
}
