gf_isom_remove_sample_fragment(GF_ISOFile *movie, u32 trackNumber, u32 sampleNumber)
{
	GF_TrackBox *trak;
	GF_Err e;

	e = CanAccessMovie(movie, GF_ISOM_OPEN_WRITE);
	if (e) return e;

	trak = gf_isom_get_track_from_file(movie, trackNumber);
	if (!trak) return GF_BAD_PARAM;
	return stbl_RemoveSampleFragments(trak->Media->information->sampleTable, sampleNumber);
}
