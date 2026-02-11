update_trun_offsets(GF_ISOFile *movie, s32 offset)
{
#ifndef USE_BASE_DATA_OFFSET
	GF_TrackFragmentRunBox *trun;
	u32 i, j;
	GF_TrackFragmentBox *traf;
	i=0;
	while ((traf = gf_list_enum(movie->moof->TrackList, &i))) {

		traf->tfhd->base_data_offset = 0;
		j=0;
		while ((trun =  gf_list_enum(traf->TrackRuns, &j))) {
			if (j==1) {
				trun->data_offset += offset;
			} else {
				trun->data_offset = 0;
			}
		}
	}
#endif
}
