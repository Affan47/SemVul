replace_u(char *str, char *username)
{
	char *entry = NULL, *p = str;
	size_t usz = username ? strlen(username) : 0;

	while (*p) {
		size_t sz;
		char *tp, *old = entry;

		if (memcmp(p, "\\u", 2)) {
			p++;
			continue;
		}
		sz = strlen(str);

		if (p == str && sz == 2)

			return username;

		tp = entry = malloc(sz + usz);
		if (!tp)
			log_err(_("failed to allocate memory: %m"));

		if (p != str) {

			memcpy(tp, str, p - str);
			tp += p - str;
		}
		if (usz) {

			memcpy(tp, username, usz);
			tp += usz;
		}
		if (*(p + 2))

			memcpy(tp, p + 2, sz - (p - str) - 1);
		else
			*tp = '\0';

		p = tp;
		str = entry;
		free(old);
	}

	return entry ? entry : str;
}
