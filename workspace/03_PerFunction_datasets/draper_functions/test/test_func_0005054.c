make_admin_credentials(void)
{
  char *expires, *role_str, *ua_str, *validity;

  if ((expires = conf_val(CONF_AUTH_CREDENTIALS_ADMIN_LIFETIME_SECS)) == NULL)
	expires = AUTH_CREDENTIALS_ADMIN_DEFAULT_LIFETIME_SECS;

  role_str = "";
  validity = AUTH_VALID_FOR_ACS;
  ua_str = NULL;

  return(make_credentials(NULL, NULL, make_dacs_admin_name("DACS-ADMIN"),
						  "", role_str, expires,
						  AUTH_STYLE_ADMIN, validity, NULL, ua_str));
}
