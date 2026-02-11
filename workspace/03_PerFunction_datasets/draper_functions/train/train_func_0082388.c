cp_parser_base_clause (cp_parser* parser)
{
  tree bases = NULL_TREE;


  cp_parser_require (parser, CPP_COLON, "`:'");


  while (true)
    {
      cp_token *token;
      tree base;


      base = cp_parser_base_specifier (parser);

      if (base != error_mark_node)
	{
	  TREE_CHAIN (base) = bases;
	  bases = base;
	}

      token = cp_lexer_peek_token (parser->lexer);

      if (token->type != CPP_COMMA)
	break;

      cp_lexer_consume_token (parser->lexer);
    }


  parser->scope = NULL_TREE;
  parser->qualifying_scope = NULL_TREE;
  parser->object_scope = NULL_TREE;

  return nreverse (bases);
}
