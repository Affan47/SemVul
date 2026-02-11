xstrndup(const char *s, int n)
{
	int m;
	char *t;

	if (ENABLE_DEBUG && s == NULL)
		bb_error_msg_and_die("xstrndup bug");


	m = n;
	t = (char*) s;
	while (m) {
		if (!*t) break;
		m--;
		t++;
	}
	n -= m;
	t = xmalloc(n + 1);
	t[n] = '\0';

	return memcpy(t, s, n);
}
