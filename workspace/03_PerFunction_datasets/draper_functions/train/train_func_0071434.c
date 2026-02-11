hid_lookup_path(const HIDNode_t usage, usage_tables_t *utab)
{
	int i, j;

	for (i = 0; utab[i] != NULL; i++)
	{
		for (j = 0; utab[i][j].usage_name != NULL; j++)
		{
			if (utab[i][j].usage_code != usage)
				continue;

			upsdebugx(5, "hid_lookup_path: %08x -> %s", (unsigned int)usage, utab[i][j].usage_name);
			return utab[i][j].usage_name;
		}
	}

	upsdebugx(5, "hid_lookup_path: %08x -> not found in lookup table", (unsigned int)usage);
	return NULL;
}
