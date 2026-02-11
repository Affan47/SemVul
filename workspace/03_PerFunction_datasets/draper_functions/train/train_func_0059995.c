string_append_c(string_t s, char c)
{
	if (!s) {
		errno = EFAULT;
		return -1;
	}

	string_realloc(s, s->len + 1);

	s->str[s->len++] = c;
	s->str[s->len] = '\0';

	return 0;
}
