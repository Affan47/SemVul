cp_parser_base_clause (cp_parser* parser)
{
  tree bases = NULL_TREE;


  cp_parser_require (parser, CPP_COLON, RT_COLON);


  while (true)
    {
      cp_token *token;
      tree base;
      bool pack_expansion_p = false;


      base = cp_parser_base_specifier (parser);

      if (cp_lexer_next_token_is (parser->lexer, CPP_ELLIPSIS))
        {

          cp_lexer_consume_token (parser->lexer);

          pack_expansion_p = true;
        }


      if (base && base != error_mark_node)
	{
          if (pack_expansion_p)

            TREE_VALUE (base) = make_pack_expansion (TREE_VALUE (base));

          if (!check_for_bare_parameter_packs (TREE_VALUE (base)))
            {
              TREE_CHAIN (base) = bases;
              bases = base;
            }
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
