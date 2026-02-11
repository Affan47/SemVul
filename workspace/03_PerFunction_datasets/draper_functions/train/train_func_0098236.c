SEI_realloc(WordEntry **in, uint32 *len)
{
	if (*len == 0 || in == NULL)
	{
		*len = 8;
		in = palloc(sizeof(WordEntry *) * (*len));
	}
	else
	{
		*len *= 2;
		in = repalloc(in, sizeof(WordEntry *) * (*len));
	}
	return in;
}
