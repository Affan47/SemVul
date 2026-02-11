addDatum(KeyArray *keys, Datum datum, GinNullCategory category)
{
	if (keys->nvalues >= keys->maxvalues)
	{
		keys->maxvalues *= 2;
		keys->keys = (Datum *)
			repalloc(keys->keys, sizeof(Datum) * keys->maxvalues);
		keys->categories = (GinNullCategory *)
			repalloc(keys->categories, sizeof(GinNullCategory) * keys->maxvalues);
	}

	keys->keys[keys->nvalues] = datum;
	keys->categories[keys->nvalues] = category;
	keys->nvalues++;
}
