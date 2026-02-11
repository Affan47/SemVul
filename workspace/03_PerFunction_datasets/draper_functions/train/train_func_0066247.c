dump_timed_text_track(GF_ISOFile *file, u32 trackID, char *inName, Bool is_convert, u32 dump_type)
{
	FILE *dump;
	GF_Err e;
	u32 track;
	char szBuf[1024];

	track = gf_isom_get_track_by_id(file, trackID);
	if (!track) {
		fprintf(stderr, "Cannot find track ID %d\n", trackID);
		return;
	}

	switch (gf_isom_get_media_type(file, track)) {
	case GF_ISOM_MEDIA_TEXT:
	case GF_ISOM_MEDIA_SUBT:
		break;
	default:
		fprintf(stderr, "Track ID %d is not a 3GPP text track\n", trackID);
		return;
	}

	if (inName) {
		if (is_convert)
			sprintf(szBuf, "%s.%s", inName, (dump_type==2) ? "svg" : ((dump_type==1) ? "srt" : "ttxt") ) ;
		else
			sprintf(szBuf, "%s_%d_text.%s", inName, trackID, (dump_type==2) ? "svg" : ((dump_type==1) ? "srt" : "ttxt") );
		dump = gf_f64_open(szBuf, "wt");
	} else {
		dump = stdout;
	}
	e = gf_isom_text_dump(file, track, dump, dump_type);
	if (inName) fclose(dump);

	if (e) fprintf(stderr, "Conversion failed (%s)\n", gf_error_to_string(e));
	else fprintf(stderr, "Conversion done\n");
}
