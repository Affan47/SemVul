free_all_streams()
{
	int i;

	for (i = 0; i < MAX_STREAMS; i++)
	{
		if (st[i])
			free1(st[i]);
		st[i] = NULL;

	}
}
