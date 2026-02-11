gf_isom_remove_sample_fragments(GF_ISOFile *movie, u32 trackNumber)
{
	GF_TrackBox *trak;
	GF_Err e;

	e = CanAccessMovie(movie, GF_ISOM_OPEN_WRITE);
	if (e) return e;

	trak = gf_isom_get_track_from_file(movie, trackNumber);
	if (!trak) return GF_BAD_PARAM;

	if (trak->Media->information->sampleTable->Fragments) {
		gf_isom_box_del((GF_Box *)trak->Media->information->sampleTable->Fragments);
		trak->Media->information->sampleTable->Fragments = NULL;
	}
	return GF_OK;
}
