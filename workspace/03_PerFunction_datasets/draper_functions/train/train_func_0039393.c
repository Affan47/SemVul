brasero_caps_session_get_image_flags (BraseroTrackType *input,
                                     BraseroTrackType *output,
                                     BraseroBurnFlag *supported,
                                     BraseroBurnFlag *compulsory)
{
	BraseroBurnFlag compulsory_flags = BRASERO_BURN_FLAG_NONE;
	BraseroBurnFlag supported_flags = BRASERO_BURN_FLAG_CHECK_SIZE|BRASERO_BURN_FLAG_NOGRACE;

	BRASERO_BURN_LOG ("FLAGS: image required");


	if (brasero_track_type_get_has_medium (input))
		supported_flags |= BRASERO_BURN_FLAG_EJECT;

	*supported = supported_flags;
	*compulsory = compulsory_flags;

	BRASERO_BURN_LOG_FLAGS (supported_flags, "FLAGS: supported");
	BRASERO_BURN_LOG_FLAGS (compulsory_flags, "FLAGS: compulsory");

	return BRASERO_BURN_OK;
}
