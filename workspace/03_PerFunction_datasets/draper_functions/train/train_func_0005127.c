gf_dash_segmenter_probe_input(GF_DashSegInput *dash_input)
{
	FILE *t = gf_f64_open(dash_input->file_name, "rb");
	if (!t) return GF_URL_ERROR;
	fclose(t);
#ifndef GPAC_DISABLE_ISOM_FRAGMENTS
	if (gf_isom_probe_file(dash_input->file_name)) {
		strcpy(dash_input->szMime, "video/mp4");
		dash_input->dasher_create_init_segment = dasher_isom_create_init_segment;
		dash_input->dasher_input_classify = dasher_isom_classify_input;
		dash_input->dasher_get_components_info = dasher_isom_get_input_components_info;
		dash_input->dasher_segment_file = dasher_isom_segment_file;
		return GF_OK;
	}
#endif

#ifndef GPAC_DISABLE_MPEG2TS
	if (gf_m2ts_probe_file(dash_input->file_name)) {
		GF_TSSegmenter ts_seg;
		u32 count = 0;
		GF_Err e = dasher_get_ts_demux(&ts_seg, dash_input->file_name, 1);
		if (e) return e;
		count = gf_list_count(ts_seg.ts->programs);
		dasher_del_ts_demux(&ts_seg);
		if (count>1) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_DASH, ("[DASH]: MPEG-2 TS file %s has several programs - this is not supported in MPEG-DASH - skipping\n", dash_input->file_name));
			return GF_NOT_SUPPORTED;
		}

		strcpy(dash_input->szMime, "video/mp2t");

		dash_input->dasher_create_init_segment = NULL;
		dash_input->dasher_input_classify = dasher_generic_classify_input;
		dash_input->dasher_get_components_info = dasher_mp2t_get_components_info;
		dash_input->dasher_segment_file = dasher_mp2t_segment_file;
		return GF_OK;
	}
#endif

	GF_LOG(GF_LOG_ERROR, GF_LOG_DASH, ("[DASH]: File %s not supported for dashing - skipping\n", dash_input->file_name));
	return GF_NOT_SUPPORTED;
}
