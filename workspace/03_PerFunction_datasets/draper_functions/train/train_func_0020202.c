FormMCDIdata(char* mcdi_data) {
	uint16_t mcdi_len = 0;
	uint8_t first_track = 0;
	uint8_t last_track = 0;

	CD_TDesc* track_TOC_desc = cdTOC->track_description;

	if (cdTOC->track_description != NULL) {
		mcdi_len +=4;

		while (track_TOC_desc != NULL) {
			if (track_TOC_desc->tracknumber >= 1 && track_TOC_desc->tracknumber <= 99 && !DataControlField(track_TOC_desc->controladdress)) {
				mcdi_len += FillSingleMCDIentry(track_TOC_desc, mcdi_data+mcdi_len);
				if (first_track == 0) {
					first_track = track_TOC_desc->tracknumber;
				}
				last_track = track_TOC_desc->tracknumber;
			}
			track_TOC_desc = (CD_TDesc*)track_TOC_desc->next_description;
		}
		if (mcdi_len > 0) {
			CD_TDesc* leadout = LeadOutTrack(cdTOC);
			if (leadout != NULL) {
				mcdi_len += FillSingleMCDIentry(leadout, mcdi_data+mcdi_len);
			}
		}

		UInt16_TO_String2(mcdi_len, mcdi_data);
		mcdi_data[2] = first_track;
		mcdi_data[3] = last_track;
	}
	return mcdi_len;
}
