opj_destroy_compress(opj_cinfo_t *cinfo) {
	if(cinfo) {

		switch(cinfo->codec_format) {
			case CODEC_J2K:
				j2k_destroy_compress((opj_j2k_t*)cinfo->j2k_handle);
				break;
			case CODEC_JP2:
				jp2_destroy_compress((opj_jp2_t*)cinfo->jp2_handle);
				break;
			case CODEC_JPT:
			case CODEC_UNKNOWN:
			default:
				break;
		}

		opj_free(cinfo);
	}
}
