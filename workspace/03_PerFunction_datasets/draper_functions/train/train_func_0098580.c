auth_token_get(char *item_type, char *username)
{
  char *token_str;
  Auth_token *token;

  if ((token_str = auth_token_get_flattened(item_type, username)) == NULL)
	return(NULL);

  if ((token = auth_token_unflatten(token_str, item_type)) == NULL)
	return(NULL);

  return(token);
}
