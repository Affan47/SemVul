cp_parser_declaration_seq_opt (cp_parser* parser)
{
  while (true)
    {
      cp_token *token;

      token = cp_lexer_peek_token (parser->lexer);

      if (token->type == CPP_CLOSE_BRACE
	  || token->type == CPP_EOF
	  || token->type == CPP_PRAGMA_EOL)
	break;

      if (token->type == CPP_SEMICOLON)
	{


	  cp_lexer_consume_token (parser->lexer);
	  if (!in_system_header)
	    pedwarn (input_location, OPT_Wpedantic, "extra %<;%>");
	  continue;
	}


      if (!parser->implicit_extern_c && token->implicit_extern_c)
	{
	  push_lang_context (lang_name_c);
	  parser->implicit_extern_c = true;
	}
      else if (parser->implicit_extern_c && !token->implicit_extern_c)
	{
	  pop_lang_context ();
	  parser->implicit_extern_c = false;
	}

      if (token->type == CPP_PRAGMA)
	{


	  cp_parser_pragma (parser, pragma_external);
	  continue;
	}


      cp_parser_declaration (parser);
    }
}
