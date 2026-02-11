gf_sm_finalize_mux(GF_ISOFile *mp4, GF_ESD *src, u32 offset_ts)
{
#if !defined (GPAC_DISABLE_ISOM) && !defined(GPAC_DISABLE_ISOM_WRITE)
	u32 track, mts, ts;
	GF_MuxInfo *mux = gf_sm_get_mux_info(src);
	if (!mux && !offset_ts) return;
	track = gf_isom_get_track_by_id(mp4, src->ESID);
	if (!track) return;

	mts = gf_isom_get_media_timescale(mp4, track);
	ts = gf_isom_get_timescale(mp4);

	if (mux) offset_ts += mux->startTime * mts / 1000;
	if (offset_ts) {
		u32 off = offset_ts * ts  / mts;
		u64 dur = gf_isom_get_media_duration(mp4, track);
		dur = dur * ts / mts;
		gf_isom_set_edit_segment(mp4, track, 0, off, 0, GF_ISOM_EDIT_EMPTY);
		gf_isom_set_edit_segment(mp4, track, off, dur, 0, GF_ISOM_EDIT_NORMAL);
	}

	if (mux) {
		if (mux->GroupID) gf_isom_set_track_group(mp4, track, mux->GroupID);
#ifndef GPAC_DISABLE_MEDIA_IMPORT
		if (mux->import_flags & GF_IMPORT_USE_COMPACT_SIZE)
			gf_isom_use_compact_size(mp4, track, 1);
#endif
	}
#endif
}
