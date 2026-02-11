joe_wcwidth(int wide, unsigned int ucs)
{


	if (!locale_map->type || !wide)
		return (1);

	if ((wide = unictrl(ucs)))
		return (wide);


	if (mb_ucsbsearch(mb_ucs_combining, NELEM(mb_ucs_combining), ucs) != (size_t)-1)
		return (0);


	if (mb_ucsbsearch(mb_ucs_fullwidth, NELEM(mb_ucs_fullwidth), ucs) != (size_t)-1)
		return (2);
	return (1);
}
