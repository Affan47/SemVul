info_loader(AWEOps *ops, SFInfo *sf, LayerTable *tbl, LoadList *request)
{
	static awe_voice_rec_patch vrec;
	awe_voice_info *vp = &vrec.info;


	if (request->map.bank > 0 || awe_option.default_bank < 0)
		vrec.hdr.bank = request->map.bank;
	else
		vrec.hdr.bank = awe_option.default_bank;
	vrec.hdr.instr = request->map.preset;
	vrec.hdr.nvoices = 1;
	if (info_write_count_inc(vrec.hdr.instr) == 1)
		vrec.hdr.write_mode = AWE_WR_REPLACE;
	else
		vrec.hdr.write_mode = AWE_WR_APPEND;


	set_sample_info(sf, vp, tbl);
	set_init_info(sf, vp, tbl);
	set_rootkey(sf, vp, tbl);
	set_modenv(sf, vp, tbl);
	set_volenv(sf, vp, tbl);
	set_lfo1(sf, vp, tbl);
	set_lfo2(sf, vp, tbl);

	memset(vp->parm.reserved, 0, sizeof(vp->parm.reserved));


	if (request->map.keynote != -1 &&
	    request->pat.keynote != request->map.keynote) {
		vp->low = vp->high = request->map.keynote;
		vp->fixkey = request->map.keynote;
	}


	vrec.patch.optarg = 0;
	vrec.patch.len = AWE_VOICE_REC_SIZE + AWE_VOICE_INFO_SIZE;
	vrec.patch.type = AWE_LOAD_INFO;
	vrec.patch.reserved = 0;


	if (ops->load_patch(&vrec, sizeof(vrec)) < 0) {
		if (awe_verbose)
			fprintf(stderr, "awe: can't load voice info\n");
		return AWE_RET_ERR;
	}

	return AWE_RET_OK;
}
