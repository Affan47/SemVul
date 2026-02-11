SetCondition(ARGS * ap)
{
	const char *	str;

	if ((ap->count <= 0) || (**ap->table == '-'))
	{
		fprintf(stderr, "Missing condition expression\n");

		return FALSE;
	}

	ap->count--;
	str = *ap->table++;

	return ParseCondition(str);
}
