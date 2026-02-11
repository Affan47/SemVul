flag_comp_union(bitflag *flags1, const bitflag *flags2, const size_t size)
{
	size_t i;
	bool delta = FALSE;

	for (i = 0; i < size; i++)
	{

		if (!(~flags1[i] & ~flags2[i])) delta = TRUE;

		flags1[i] |= ~flags2[i];
	}

	return delta;
}
