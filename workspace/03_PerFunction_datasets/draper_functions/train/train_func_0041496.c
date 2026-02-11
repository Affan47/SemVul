ea_check_size(struct gfs2_sbd *sdp, unsigned int nsize, size_t dsize)
{
	unsigned int size;

	if (dsize > GFS2_EA_MAX_DATA_LEN)
		return -ERANGE;

	ea_calc_size(sdp, nsize, dsize, &size);


	if (size > sdp->sd_jbsize)
		return -ERANGE;

	return 0;
}
