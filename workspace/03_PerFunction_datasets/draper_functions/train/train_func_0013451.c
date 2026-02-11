filename_beautify(const char *filename)
{
	const char *s;
	char *q;
	uchar c;
	size_t len;
	size_t j = 0;
	static const char punct[] = "_-+=.,<>{}[]";
	static const char strip[] = "_-.";
	static const char empty[] = "{empty}";

	g_assert(filename);

	s = filename;
	len = strlen(filename);
	q = halloc(len + 1);

	while ((c = *s++)) {
		uchar d;


		if (j == 0) {
			if (NULL == strchr(strip, c))
				q[j++] = c;
			continue;
		}

		g_assert(j > 0);

		d = q[j - 1];


		if (d == '_' && NULL != strchr(punct, c)) {
			q[j - 1] = c;
			continue;
		}


		if (NULL != strchr(&punct[1], d) && c == '_')
			continue;

		q[j++] = c;
	}

	g_assert(j <= len);
	q[j] = '\0';


	if (j == 0) {
		HFREE_NULL(q);
		return h_strdup(empty);
	}


	if (NULL == strchr(q, '.') && j < len && '.' == filename[len - j]) {
		char *r = h_strconcat(empty, ".", q, (void *) 0);
		HFREE_NULL(q);

		return r;
	}

	return q;
}
