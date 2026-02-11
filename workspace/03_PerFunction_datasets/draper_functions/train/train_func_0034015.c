DatumGetExpandedArray(Datum d)
{

	if (VARATT_IS_EXTERNAL_EXPANDED_RW(DatumGetPointer(d)))
	{
		ExpandedArrayHeader *eah = (ExpandedArrayHeader *) DatumGetEOHP(d);

		Assert(eah->ea_magic == EA_MAGIC);
		return eah;
	}


	d = expand_array(d, CurrentMemoryContext, NULL);
	return (ExpandedArrayHeader *) DatumGetEOHP(d);
}
