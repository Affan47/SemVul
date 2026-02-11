chirp_client_md5(struct chirp_client * c, const char *path, unsigned char digest[16], time_t stoptime)
{
	INT64_T result;
	INT64_T actual;

	char safepath[CHIRP_LINE_MAX];
	url_encode(path, safepath, sizeof(safepath));

	result = simple_command(c, stoptime, "md5 %s\n", path);

	if(result == 16) {
		actual = link_read(c->link, (char *) digest, 16, stoptime);
		if(actual != result) {
			errno = ECONNRESET;
			result = -1;
		}

	} else if(result >= 0) {
		result = -1;
		errno = ECONNRESET;
	}
	return result;
}
