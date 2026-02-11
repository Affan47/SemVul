ctpl_token_append (CtplToken *token,
                   CtplToken *brother)
{
  CtplToken *first_tok = token;

  if (token->last) {
    token = token->last;
  }
  while (token->next) {
    token = token->next;
  }
  token->next = brother;
  token->last = brother->last ? brother->last : brother;
  first_tok->last = token->last;
}
