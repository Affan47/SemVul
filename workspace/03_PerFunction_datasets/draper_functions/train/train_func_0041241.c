smtp_auth_md5(int fd, char *login, char *password)
{
	unsigned char digest[BUF_SIZE];
	char buffer[BUF_SIZE], ascii_digest[33];
	char *temp;
	int len, i;
	static char hextab[] = "0123456789abcdef";

	temp = calloc(BUF_SIZE, 1);
	memset(buffer, 0, sizeof(buffer));
	memset(digest, 0, sizeof(digest));
	memset(ascii_digest, 0, sizeof(ascii_digest));


	send_remote_command(fd, "AUTH CRAM-MD5");
	if (read_remote(fd, sizeof(buffer), buffer) != 3) {
		syslog(LOG_DEBUG, "smarthost authentication:"
		       " AUTH cram-md5 not available: %s", neterr);

		free(temp);
		return (-1);
	}


	base64_decode(buffer + 4, temp);
	hmac_md5((unsigned char *)temp, strlen(temp),
		 (unsigned char *)password, strlen(password), digest);
	free(temp);

	ascii_digest[32] = 0;
	for (i = 0; i < 16; i++) {
		ascii_digest[2*i] = hextab[digest[i] >> 4];
		ascii_digest[2*i+1] = hextab[digest[i] & 15];
	}


	snprintf(buffer, BUF_SIZE, "%s %s", login, ascii_digest);


	len = base64_encode(buffer, strlen(buffer), &temp);
	if (len < 0) {
		syslog(LOG_ERR, "can not encode auth reply: %m");
		return (-1);
	}


	send_remote_command(fd, "%s", temp);
	free(temp);
	if (read_remote(fd, 0, NULL) != 2) {
		syslog(LOG_WARNING, "remote delivery deferred:"
				" AUTH cram-md5 failed: %s", neterr);
		return (-2);
	}

	return (0);
}
