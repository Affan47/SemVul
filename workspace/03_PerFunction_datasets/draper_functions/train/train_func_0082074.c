enlargeStringInfo(StringInfo str, int needed)
{
	int			newlen;


	if (needed < 0 ||
		((Size) needed) >= (MaxAllocSize - (Size) str->len))
		elog(ERROR, "invalid string enlargement request size %d",
			 needed);

	needed += str->len + 1;


	if (needed <= str->maxlen)
		return;


	newlen = 2 * str->maxlen;
	while (needed > newlen)
		newlen = 2 * newlen;


	if (newlen > (int) MaxAllocSize)
		newlen = (int) MaxAllocSize;

	str->data = (char *) repalloc(str->data, newlen);

	str->maxlen = newlen;
}
