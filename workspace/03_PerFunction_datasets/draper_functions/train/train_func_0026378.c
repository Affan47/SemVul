credentials_externalize(Credentials *credentials, char **buf)
{
  int length;
  Crypt_keys *ck;

  if (credentials == NULL) {
	*buf = "";
	return(0);
  }

  ck = crypt_keys_from_vfs(ITEM_TYPE_FEDERATION_KEYS);
  length = credentials_externalize_with_keys(credentials, ck, buf);

  return(length);
}
