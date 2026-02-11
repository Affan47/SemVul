__env_fetch_flags(flagmap, mapsize, inflagsp, outflagsp)
	const FLAG_MAP *flagmap;
	u_int mapsize;
	u_int32_t *inflagsp, *outflagsp;
{
	const FLAG_MAP *fmp;
	u_int32_t i;

	*outflagsp = 0;
	for (i = 0, fmp = flagmap;
	    i < mapsize / sizeof(flagmap[0]); ++i, ++fmp)
		if (FLD_ISSET(*inflagsp, fmp->outflag))
			FLD_SET(*outflagsp, fmp->inflag);
}
