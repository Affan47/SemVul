gf_isom_datamap_open(GF_MediaBox *mdia, u32 dataRefIndex, u8 Edit)
{
	GF_DataEntryBox *ent;
	GF_MediaInformationBox *minf;
	u32 SelfCont;
	GF_Err e = GF_OK;
	if ((mdia == NULL) || (! mdia->information) || !dataRefIndex)
		return GF_ISOM_INVALID_MEDIA;

	minf = mdia->information;

	if (dataRefIndex > gf_list_count(minf->dataInformation->dref->other_boxes))
		return GF_BAD_PARAM;

	ent = (GF_DataEntryBox*)gf_list_get(minf->dataInformation->dref->other_boxes, dataRefIndex - 1);
	if (ent == NULL) return GF_ISOM_INVALID_MEDIA;


	if ((minf->dataEntryIndex == dataRefIndex) && (ent->flags != 1)) {
		return GF_OK;
	}


	if (minf->dataHandler) gf_isom_datamap_close(minf);

	SelfCont = 0;
	switch (ent->type) {
	case GF_ISOM_BOX_TYPE_URL:
	case GF_ISOM_BOX_TYPE_URN:
		if (ent->flags == 1) SelfCont = 1;
		break;
	default:
		SelfCont = 1;
		break;
	}

	if (SelfCont) {

		if (!Edit) {
			if (mdia->mediaTrack->moov->mov->movieFileMap == NULL) return GF_ISOM_INVALID_FILE;
			minf->dataHandler = mdia->mediaTrack->moov->mov->movieFileMap;
		} else {
#ifndef GPAC_DISABLE_ISOM_WRITE
			if (mdia->mediaTrack->moov->mov->editFileMap == NULL) return GF_ISOM_INVALID_FILE;
			minf->dataHandler = mdia->mediaTrack->moov->mov->editFileMap;
#else

			return GF_BAD_PARAM;
#endif
		}

	} else {
		e = gf_isom_datamap_new(ent->location, mdia->mediaTrack->moov->mov->fileName, GF_ISOM_DATA_MAP_READ, & mdia->information->dataHandler);
		if (e) return (e==GF_URL_ERROR) ? GF_ISOM_UNKNOWN_DATA_REF : e;
	}

	minf->dataEntryIndex = dataRefIndex;
	return GF_OK;
}
