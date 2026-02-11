cp_parser_asm_specification_opt (cp_parser* parser)
{
  cp_token *token;
  tree asm_specification;


  token = cp_lexer_peek_token (parser->lexer);


  if (!cp_parser_is_keyword (token, RID_ASM))
    return NULL_TREE;


  cp_lexer_consume_token (parser->lexer);

  cp_parser_require (parser, CPP_OPEN_PAREN, "`('");


  token = cp_parser_require (parser, CPP_STRING, "string-literal");
  if (token)
    asm_specification = token->value;
  else
    asm_specification = NULL_TREE;


  cp_parser_require (parser, CPP_CLOSE_PAREN, "`('");

  return asm_specification;
}
