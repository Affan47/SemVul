gel_decode_string (const char *s)
{
	if (s == NULL)
		return NULL;
	if (s[0] == 'A') {
		return g_strdup (&(s[1]));
	} else if (s[0] == 'B') {
		gsize len;
		char *p = (char *)g_base64_decode (&(s[1]), &len);
		if (p == NULL || len < 0)
			return NULL;
		p = g_realloc (p, len+1);
		p[len] = '\0';
		return p;
	} else if (s[0] == 'E') {
		return g_strdup ("");
	} else {
		g_warning ("gel_decode_string: bad string!");
		return NULL;
	}
}
