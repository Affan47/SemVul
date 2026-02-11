auth_token_get_all(char *item_type)
{
  int i;
  Auth_token *token;
  Dsvec *dsv, *tokens;

  if ((dsv = auth_token_list(item_type)) == NULL)
	return(NULL);

  tokens = dsvec_init(NULL, sizeof(Auth_token));
  for (i = 0; i < dsvec_len(dsv); i++) {
	char *u;

	u = (char *) dsvec_ptr_index(dsv, i);
	if ((token = auth_token_get(item_type, u)) == NULL)
	  return(NULL);
	dsvec_add_ptr(tokens, token);
  }

  return(tokens);
}
