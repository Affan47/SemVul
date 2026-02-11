brasero_data_session_is_valid_multi (BraseroMedium *medium)
{
	BraseroMedia media;
	BraseroMedia media_status;

	media = brasero_medium_get_status (medium);
	media_status = brasero_burn_library_get_media_capabilities (media);

	return (media_status & BRASERO_MEDIUM_WRITABLE) &&
	       (media & BRASERO_MEDIUM_HAS_DATA) &&
	       (brasero_medium_get_last_data_track_address (medium, NULL, NULL) != -1);
}
