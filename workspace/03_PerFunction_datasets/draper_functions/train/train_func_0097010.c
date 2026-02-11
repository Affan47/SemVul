gf_isom_is_omadrm_media(GF_ISOFile *the_file, u32 trackNumber, u32 sampleDescriptionIndex)
{
	GF_TrackBox *trak;
	GF_ProtectionInfoBox *sinf;

	trak = gf_isom_get_track_from_file(the_file, trackNumber);
	if (!trak) return 0;

	sinf = gf_isom_get_sinf_entry(trak, sampleDescriptionIndex, GF_ISOM_OMADRM_SCHEME, NULL);
	if (!sinf) return 0;


	if (!sinf->info || !sinf->info->okms || !sinf->info->okms->hdr)
		return 0;

	return 1;
}
