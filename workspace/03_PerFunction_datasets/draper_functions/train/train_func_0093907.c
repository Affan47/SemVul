f1x_early_channel_count(struct amd64_pvt *pvt)
{
	int i, j, channels = 0;


	if (pvt->fam == 0x10 && (pvt->dclr0 & WIDTH_128))
		return 2;


	edac_dbg(0, "Data width is not 128 bits - need more decoding\n");


	for (i = 0; i < 2; i++) {
		u32 dbam = (i ? pvt->dbam1 : pvt->dbam0);

		for (j = 0; j < 4; j++) {
			if (DBAM_DIMM(j, dbam) > 0) {
				channels++;
				break;
			}
		}
	}

	if (channels > 2)
		channels = 2;

	amd64_info("MCT channel count: %d\n", channels);

	return channels;
}
