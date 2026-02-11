_next_CD_TEXT_pack (BraseroScsiCDTextData *cd_text,
		    int current,
		    int max)
{
	current ++;
	if (current >= max)
		return -1;


	while (cd_text->pack [current].type != BRASERO_SCSI_CD_TEXT_ALBUM_TITLE &&
	       cd_text->pack [current].type != BRASERO_SCSI_CD_TEXT_PERFORMER_NAME &&
	       cd_text->pack [current].type != BRASERO_SCSI_CD_TEXT_SONGWRITER_NAME &&
	       cd_text->pack [current].type != BRASERO_SCSI_CD_TEXT_COMPOSER_NAME &&
	       cd_text->pack [current].type != BRASERO_SCSI_CD_TEXT_ARRANGER_NAME &&
	       cd_text->pack [current].type != BRASERO_SCSI_CD_TEXT_ARTIST_NAME &&
	       cd_text->pack [current].type != BRASERO_SCSI_CD_TEXT_DISC_ID_INFO &&
	       cd_text->pack [current].type != BRASERO_SCSI_CD_TEXT_GENRE_ID_INFO &&
	       cd_text->pack [current].type != BRASERO_SCSI_CD_TEXT_UPC_EAN_ISRC &&
	       cd_text->pack [current].type != BRASERO_SCSI_CD_TEXT_BLOCK_SIZE) {
		current ++;
		if (current >= max)
			return -1;
	}

	return current;
}
