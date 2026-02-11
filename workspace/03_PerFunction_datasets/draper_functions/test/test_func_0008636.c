gf_odf_hevc_cfg_write_bs(GF_HEVCConfig *cfg, GF_BitStream *bs)
{
	u32 i, count;

	gf_bs_write_int(bs, cfg->configurationVersion, 8);
	gf_bs_write_int(bs, cfg->profile_space, 3);
	gf_bs_write_int(bs, cfg->profile_idc, 5);
	gf_bs_write_int(bs, cfg->constraint_indicator_flags, 16);
	gf_bs_write_int(bs, cfg->level_idc, 8);
	gf_bs_write_int(bs, cfg->profile_compatibility_indications, 32);
	gf_bs_write_int(bs, 0xFF, 6);
	gf_bs_write_int(bs, cfg->chromaFormat, 2);
	gf_bs_write_int(bs, 0xFF, 5);
	gf_bs_write_int(bs, cfg->luma_bit_depth-8, 3);
	gf_bs_write_int(bs, 0xFF, 5);
	gf_bs_write_int(bs, cfg->chroma_bit_depth-8, 3);
	gf_bs_write_int(bs, cfg->avgFrameRate, 16);
	gf_bs_write_int(bs, cfg->constantFrameRate, 2);
	gf_bs_write_int(bs, cfg->numTemporalLayers, 3);
	gf_bs_write_int(bs, 1, 1);
	gf_bs_write_int(bs, cfg->nal_unit_size - 1, 2);

	count = gf_list_count(cfg->param_array);
	gf_bs_write_int(bs, count, 8);
	for (i=0; i<count; i++) {
		u32 nalucount, j;
		GF_HEVCParamArray *ar = gf_list_get(cfg->param_array, i);
		gf_bs_write_int(bs, ar->array_completeness, 1);
		gf_bs_write_int(bs, 0, 1);
		gf_bs_write_int(bs, ar->type, 6);
		nalucount = gf_list_count(ar->nalus);
		gf_bs_write_int(bs, nalucount, 16);
		for (j=0; j<nalucount; j++) {
			GF_AVCConfigSlot *sl = (GF_AVCConfigSlot *)gf_list_get(ar->nalus, j);
			gf_bs_write_int(bs, sl->size, 16);
			gf_bs_write_data(bs, sl->data, sl->size);
		}
	}
	return GF_OK;
}
