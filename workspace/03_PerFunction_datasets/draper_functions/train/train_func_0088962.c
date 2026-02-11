DetermineCDType(CD_TOC_* cdTOCdata) {
	CD_TDesc* track_TOC_desc = cdTOCdata->track_description;
	while (track_TOC_desc != NULL) {
		if (track_TOC_desc->tracknumber >= 1 && track_TOC_desc->tracknumber <= 99 && !DataControlField(track_TOC_desc->controladdress)) {
			return CDOBJECT_AUDIOCD;
		}
		track_TOC_desc = (CD_TDesc*)track_TOC_desc->next_description;
	}
	return CDOBJECT_DATACD;
}
