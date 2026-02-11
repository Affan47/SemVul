challengeauth_response (char *username, char *password, char *challenge)
{
	int i;
	char *user;
	char *pass;
	char *passhash;
	char *key;
	char *keyhash;
	unsigned char *digest;
	GString *buf = g_string_new_len (NULL, SHA256_DIGEST_LENGTH * 2);

	user = g_strdup (username);
	*user = rfc_tolower (*username);

	pass = g_strndup (password, 10);
	passhash = str_sha256hash (pass);
	g_free (pass);

	key = g_strdup_printf ("%s:%s", user, passhash);
	g_free (user);
	g_free (passhash);

	keyhash = str_sha256hash (key);
	g_free (key);

	digest = HMAC (EVP_sha256 (), keyhash, strlen (keyhash), (unsigned char *) challenge, strlen (challenge), NULL, NULL);
	g_free (keyhash);

	for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		g_string_append_printf (buf, "%02x", (unsigned int) digest[i]);
	}

	digest = (unsigned char *) g_string_free (buf, FALSE);

	return (char *) digest;
}
