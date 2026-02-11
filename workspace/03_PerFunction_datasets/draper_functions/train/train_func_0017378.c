tlsinteract (char *buf, int buflen, int rwflag, void *arg)
{
	identity_t *identity = (identity_t *)arg;
	char *pw;
	int len;

	if(!identity)
		return 0;

	if (identity->certificate_passphrase)
	{
		pw = identity->certificate_passphrase;
		len = strlen (pw);
		if (len + 1 > buflen)
			return 0;
		strcpy (buf, pw);
		return len;
	}
	else
		return 0;
}
