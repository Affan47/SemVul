dasher_isom_get_input_components_info(GF_DashSegInput *input, GF_DASHSegmenterOptions *opts)
{
	u32 i;
	GF_ISOFile *in;
	Double dur;

	in = gf_isom_open(input->file_name, GF_ISOM_OPEN_READ, NULL);
	input->duration = 0;
	for (i=0; i<gf_isom_get_track_count(in); i++) {
		u32 mtype = gf_isom_get_media_type(in, i+1);

		if (mtype == GF_ISOM_MEDIA_HINT)
			continue;

		if (gf_isom_get_sample_count(in, i+1)<2)
			continue;

		dur = (Double) gf_isom_get_track_duration(in, i+1);
		dur /= gf_isom_get_timescale(in);
		if (!dur) {
			dur = (Double) gf_isom_get_media_duration(in, i+1);
			dur /= gf_isom_get_media_timescale(in, i+1);
		}
		if (dur > input->duration) input->duration = dur;

		input->components[input->nb_components].ID = gf_isom_get_track_id(in, i+1);
		input->components[input->nb_components].media_type = mtype;
		if (mtype == GF_ISOM_MEDIA_VISUAL) {
			gf_isom_get_visual_info(in, i+1, 1, &input->components[input->nb_components].width, &input->components[input->nb_components].height);

			input->components[input->nb_components].fps_num = gf_isom_get_media_timescale(in, i+1);

			input->components[input->nb_components].fps_denum = gf_isom_get_sample_duration(in, i+1, 2);

		}

		else if (mtype == GF_ISOM_MEDIA_AUDIO) {
			u8 bps;
			gf_isom_get_audio_info(in, i+1, 1, &input->components[input->nb_components].sample_rate, &input->components[input->nb_components].channels, &bps);
		}
		gf_isom_get_media_language(in, i+1, input->components[input->nb_components].szLang);

		input->nb_components++;
	}
	return gf_isom_close(in);
}
