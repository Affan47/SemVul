gf_isom_add_sample_reference(GF_ISOFile *movie, u32 trackNumber, u32 StreamDescriptionIndex, GF_ISOSample *sample, u64 dataOffset)
{
	GF_TrackBox *trak;
	GF_SampleEntryBox *entry;
	u32 dataRefIndex;
	u32 descIndex;
	GF_DataEntryURLBox *Dentry;
	GF_Err e;

	e = CanAccessMovie(movie, GF_ISOM_OPEN_WRITE);
	if (e) return e;

	trak = gf_isom_get_track_from_file(movie, trackNumber);
	if (!trak) return GF_BAD_PARAM;

	e = unpack_track(trak);
	if (e) return e;


	if (trak->Media->handler->handlerType == GF_ISOM_MEDIA_OD) {
		return GF_BAD_PARAM;
	}


	descIndex = StreamDescriptionIndex;
	if (!StreamDescriptionIndex) {
		descIndex = trak->Media->information->sampleTable->currentEntryIndex;
	}
	e = Media_GetSampleDesc(trak->Media, descIndex, &entry, &dataRefIndex);
	if (e) return e;
	if (!entry || !dataRefIndex) return GF_BAD_PARAM;

	trak->Media->information->sampleTable->currentEntryIndex = descIndex;


	Dentry =(GF_DataEntryURLBox*) gf_list_get(trak->Media->information->dataInformation->dref->other_boxes, dataRefIndex - 1);
	if (Dentry->flags == 1) return GF_BAD_PARAM;


	e = Media_AddSample(trak->Media, dataOffset, sample, descIndex, 0);
	if (e) return e;

	trak->Media->mediaHeader->modificationTime = gf_isom_get_mp4time();

	e = Media_SetDuration(trak);
	if (e) return e;
	return SetTrackDuration(trak);

}
