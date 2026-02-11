gf_isom_get_duration(GF_ISOFile *movie)
{
#ifndef GPAC_DISABLE_ISOM_WRITE
	u32 i;
	u64 maxDur;
	GF_TrackBox *trak;
#endif

	if (!movie || !movie->moov) return 0;


#ifndef GPAC_DISABLE_ISOM_WRITE

	if (movie->openMode != GF_ISOM_OPEN_READ) {
		maxDur = 0;
		i=0;
		while ((trak = (GF_TrackBox *)gf_list_enum(movie->moov->trackList, &i))) {
			if( (movie->LastError = SetTrackDuration(trak))	) return 0;
			if (trak->Header->duration > maxDur)
				maxDur = trak->Header->duration;
		}
		movie->moov->mvhd->duration = maxDur;
	}

#endif

	return movie->moov->mvhd->duration;
}
