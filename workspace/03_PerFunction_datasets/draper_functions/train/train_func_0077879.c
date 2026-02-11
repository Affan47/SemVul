IsInIgnoreList (edict_t * source, edict_t * subject)
{
	int i;

	if (!source || !source->client)
		return 0;


	for (i = 1; i < PG_MAXPLAYERS; i++) {
		if (source->IGNORELIST[i] == subject)
			return i;
	}
	return 0;
}
