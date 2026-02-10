find_token(char *token)
{
  struct lexer_token *tok;
  if (!ntokens)
    init_ntokens();
  tok = bsearch(&token, tokens, ntokens, sizeof(tokens[0]), token_compare);
  return tok ? tok->value : 0;
}
