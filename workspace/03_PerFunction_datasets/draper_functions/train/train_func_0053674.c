passwd_make_digest(Passwd_digest_alg alg, char *passwd, Pw_entry *opw)
{
  char *digest, *salt_prefix, *salt, *salt_str, *val;
  unsigned char *buf;
  Pw_entry *ppw, pw;

  buf = crypto_make_random_buffer(PASSWD_SALT_BYTES);
  strba64((const unsigned char *) buf, PASSWD_SALT_BYTES, &salt);
  salt[PASSWD_SALT_BYTES] = '\0';
  if ((salt_prefix = conf_val(CONF_PASSWORD_SALT_PREFIX)) != NULL)
	salt_str = ds_xprintf("%s%s", salt_prefix, salt);
  else
	salt_str = salt;

  if (alg == PASSWD_ALG_CRYPT)
	digest = crypt(passwd, salt_str);
  else {
	char *digest_name;

	if ((digest_name = passwd_lookup_digest_name(alg)) == NULL) {
	  	log_msg((LOG_ALERT_LEVEL, "Invalid password digest algorithm: %d",
				 alg));
		dacs_fatal("Internal error");

	}
	crypto_passwd(digest_name, passwd, salt_str, &digest);
  }

  if (opw == NULL)
	ppw = pw_init_entry(&pw, NULL);
  else
	ppw = opw;

  ppw->alg = alg;
  ppw->salt = salt_str;
  ppw->digest = digest;
  val = pw_make_entry(ppw);

  if (opw == NULL) {
	if (salt != NULL)
	  strzap(salt);
	if (salt_str != NULL)
	  strzap(salt_str);
	strzap(passwd);
	memzap(buf, PASSWD_SALT_BYTES);
  }

  return(val);
}
