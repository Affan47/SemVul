__qam_map_flags(dbp, inflagsp, outflagsp)
	DB *dbp;
	u_int32_t *inflagsp, *outflagsp;
{
	COMPQUIET(dbp, NULL);

	if (FLD_ISSET(*inflagsp, DB_INORDER)) {
		FLD_SET(*outflagsp, DB_AM_INORDER);
		FLD_CLR(*inflagsp, DB_INORDER);
	}
}
