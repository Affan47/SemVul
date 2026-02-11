is_link(char *token)
{
	int i;
	int len = strlen(token);

	if (token[0] == '<')
		return TOKEN_NORMAL;

	if (!strncasecmp(token, "http://", 7)) {
		if (is_valid_domain(token + 7))
			return TOKEN_HTTP;
		else
			return TOKEN_NORMAL;
	}

	if (!strncasecmp(token, "ftp://", 6))
		return TOKEN_FTP;
	if (!strncasecmp(token, "log://", 6))
		return TOKEN_CUSTOM;
	if (!strncasecmp(token, "mailto:", 7))
		return TOKEN_EMAIL;
	if (!strncasecmp(token, "www.", 4) && is_valid_domain(token))
		return TOKEN_HTTP;
	if (!strncasecmp(token, "ftp.", 4) && is_valid_domain(token))
		return TOKEN_FTP;
	if (strstr(token, "://") && !ispunct(token[0])
		&& !ispunct(token[strlen(token)]))
		return TOKEN_CUSTOM;

	for (i = 0; i < len; i++) {
		if (token[i] == '@') {
			if (!ispunct(token[0]) && !ispunct(token[len - 1])) {
				if (is_valid_domain(token + i + 1))
					return TOKEN_EMAIL;
				break;
			}
		}
	}

	for (i = len; i >= 0; i--) {
		if (token[i] == '.') {
			if (!strcasecmp(token + i, ".edu")
				&& is_valid_domain(token))
				return TOKEN_HTTP;
			if (!strcasecmp(token + i, ".com")
				&& is_valid_domain(token))
				return TOKEN_HTTP;
			if (!strcasecmp(token + i, ".net")
				&& is_valid_domain(token))
				return TOKEN_HTTP;
			if (!strcasecmp(token + i, ".org")
				&& is_valid_domain(token))
				return TOKEN_HTTP;
			if (!strcasecmp(token + i, ".gov")
				&& is_valid_domain(token))
				return TOKEN_HTTP;
			break;
		}
	}
	return TOKEN_NORMAL;
}
