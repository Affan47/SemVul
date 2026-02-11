stripped_strlen(const char *s, size_t len)
{
	const char *end;


	for (end = &s[len]; end != s; end--) {
		if (!is_ascii_blank(end[-1]))
			break;
	}

	return end - s;
}
