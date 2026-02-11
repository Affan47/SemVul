strtok_free(strtok_t *s)
{
	strtok_check(s);

	if (s->len)
		wfree(s->token, s->len);

	s->magic = 0;
	WFREE(s);
}
