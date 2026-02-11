IsBlank(const char *s) {
    int len, i;

    if (NULL == s) {
		return 1;
	}

    if (0 == (len = strlen(s))) {
		return 1;
	}

    for (i = 0; i < len; ++i) {
        if (' ' != s[i]) {
			return 0;
		}
    }

    return 1;
}
