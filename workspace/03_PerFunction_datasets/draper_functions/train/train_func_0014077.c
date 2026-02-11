MGD77_entry_in_MGD77record (char *name, GMT_LONG *entry)
{
	GMT_LONG i;


	*entry = MGD77_NOT_SET;

	if (MGD77_Get_Set (name) == MGD77_CDF_SET) return (FALSE);


	if (!strcmp (name, "time")) {
		*entry = MGD77_TIME;
		return (TRUE);
	}


	for (i = 0; i < MGD77_N_DATA_EXTENDED; i++) if (!strcmp (name, mgd77defs[i].abbrev)) {
		*entry = i;
		return (TRUE);
	}

	return (FALSE);
}
