cp_parser_std_attribute_list (cp_parser *parser)
{
  tree attributes = NULL_TREE, attribute = NULL_TREE;
  cp_token *token = NULL;

  while (true)
    {
      attribute = cp_parser_std_attribute (parser);
      if (attribute == error_mark_node)
	break;
      if (attribute != NULL_TREE)
	{
	  TREE_CHAIN (attribute) = attributes;
	  attributes = attribute;
	}
      token = cp_lexer_peek_token (parser->lexer);
      if (token->type != CPP_COMMA)
	break;
      cp_lexer_consume_token (parser->lexer);
    }
  attributes = nreverse (attributes);
  return attributes;
}
