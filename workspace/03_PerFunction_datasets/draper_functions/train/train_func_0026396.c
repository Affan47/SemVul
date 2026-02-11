credentials_to_auth_cookies(Credentials *credentials, char **cookie_buf)
{
  int i, length, st;
  char *encrypted_cookie_text;
  Credentials *cr;
  Crypt_keys *ck;
  Ds ds;

  if (credentials == NULL) {
	*cookie_buf = "";
	return(0);
  }

  ds_init(&ds);
  ds.exact_flag = 1;
  ck = crypt_keys_from_vfs(ITEM_TYPE_FEDERATION_KEYS);

  st = 0;
  for (i = 0, cr = credentials; cr != NULL; cr = cr->next, i++) {
	credentials_externalize_with_keys(cr, ck, &encrypted_cookie_text);

	if (cr->cookie_name == NULL)
	  cr->cookie_name = make_auth_cookie_name(cr);

	st = ds_asprintf(&ds, "%s%s=%s", i == 0 ? "" : COOKIE_SEP_STR,
					 cr->cookie_name, encrypted_cookie_text);
	if (st == -1)
	  break;
  }

  crypt_keys_free(ck);
  if (st == -1)
	return(-1);

  *cookie_buf = ds_buf(&ds);
  length = ds_len(&ds);

  return(length);
}
