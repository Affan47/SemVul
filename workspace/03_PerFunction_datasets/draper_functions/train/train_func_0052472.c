opj_setup_decoder(opj_dinfo_t *dinfo, opj_dparameters_t *parameters) {
	if(dinfo && parameters) {
		switch(dinfo->codec_format) {
			case CODEC_J2K:
			case CODEC_JPT:
				j2k_setup_decoder((opj_j2k_t*)dinfo->j2k_handle, parameters);
				break;
			case CODEC_JP2:
				jp2_setup_decoder((opj_jp2_t*)dinfo->jp2_handle, parameters);
				break;
			case CODEC_UNKNOWN:
			default:
				break;
		}
	}
}
