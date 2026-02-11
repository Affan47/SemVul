_numclients (void)
{
	int count, i;
	edict_t *other;

	count = 0;
	for (i = 1; i <= maxclients->value; i++)
	{
		other = &g_edicts[i];
		if (other->inuse)
			count++;
	}
	return count;
}
