is_dupe (Wps * rec)
{
	lcall lc;
	int i;

	lc = call2l (rec->callsign);
	for (i = 0; i < 1000; i++)
	{
		if (lc == zone[i])
		{
			++dupes;
			fprintf (stderr, "\rRecord %ld (%s) duplicated\n", record, rec->callsign);
			return (1);
		}
	}
	return (0);
}
