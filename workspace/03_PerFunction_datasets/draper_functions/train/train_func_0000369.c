auth_sasldb (

#ifdef AUTH_SASLDB
  const char *login,
  const char *password,
  const char *service __attribute__((unused)),
  const char *realm
#else
  const char *login __attribute__((unused)),
  const char *password __attribute__((unused)),
  const char *service __attribute__((unused)),
  const char *realm __attribute__((unused))
#endif

  )
{
#ifdef AUTH_SASLDB

    char pw[1024];
    sasl_utils_t utils;
    int ret, outsize;
    const char *use_realm;
    char realm_buf[MAXHOSTNAMELEN];


    init_lame_utils(&utils);

    _sasl_check_db(&utils, (void *)0x1);

    if(!realm || !strlen(realm)) {
	ret = gethostname(realm_buf,MAXHOSTNAMELEN);
	if(ret) RETURN("NO");
	use_realm = realm_buf;
    } else {
	use_realm = realm;
    }


    ret = _sasldb_getdata(&utils, (void *)0x1, login, use_realm,
			  "userPassword", pw, 1024, &outsize);

    if (ret != SASL_OK) {
	RETURN("NO");
    }

    if (strcmp(pw, password)) {
	RETURN("NO");
    }

    RETURN("OK");
#else
    RETURN("NO");
#endif
}
