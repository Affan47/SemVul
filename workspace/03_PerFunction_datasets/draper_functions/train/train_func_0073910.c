pg_md5_encrypt(const char *passwd, const char *salt, size_t salt_len,
			   char *buf)
{
	size_t		passwd_len = strlen(passwd);
	char	   *crypt_buf = malloc(passwd_len + salt_len);
	bool		ret;

	if (!crypt_buf)
		return false;


	strcpy(crypt_buf, passwd);
	memcpy(crypt_buf + passwd_len, salt, salt_len);

	strcpy(buf, "md5");
	ret = pg_md5_hash(crypt_buf, passwd_len + salt_len, buf + 3);

	free(crypt_buf);

	return ret;
}
