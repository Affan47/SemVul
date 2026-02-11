email_matches(identification_t *constraint, identification_t *id)
{
	chunk_t c, i, diff;

	c = constraint->get_encoding(constraint);
	i = id->get_encoding(id);

	if (!c.len || i.len < c.len)
	{
		return FALSE;
	}
	if (memchr(c.ptr, '@', c.len))
	{
		return chunk_equals(c, i);
	}
	diff = chunk_create(i.ptr, i.len - c.len);
	if (!diff.len || !chunk_equals(c, chunk_skip(i, diff.len)))
	{
		return FALSE;
	}
	if (c.ptr[0] == '.')
	{
		return TRUE;
	}
	if (diff.ptr[diff.len - 1] == '@')
	{
		return TRUE;
	}
	return FALSE;
}
