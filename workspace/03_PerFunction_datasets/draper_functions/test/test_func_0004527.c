blockissubset(char *sub, char *super, int length)
{
	int i;

	for (i = 0; i < length; i++)
	{
		if ((sub[i] & super[i]) != sub[i])
		{
			return 0;
		}
	}

	return 1;
}
