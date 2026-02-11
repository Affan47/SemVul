MGD77_Get_Set (char *word)
{
	int j, k;

	for (j = 0, k = MGD77_NOT_SET; k == MGD77_NOT_SET && j < MGD77_N_DATA_EXTENDED; j++) if (!strcmp (word, mgd77defs[j].abbrev)) k = j;
	if (k == MGD77_NOT_SET && !strcmp (word, "time")) k = j;
	return ((k == MGD77_NOT_SET) ? MGD77_CDF_SET : MGD77_M77_SET);
}
