brasero_burn_caps_get_flags_same_src_dest_for_types (BraseroBurnCaps *self,
                                                     BraseroBurnSession *session,
                                                     BraseroTrackType *input,
                                                     BraseroTrackType *output,
                                                     BraseroBurnFlag *supported_ret,
                                                     BraseroBurnFlag *compulsory_ret)
{
	GSList *iter;
	gboolean type_supported;
	BraseroBurnResult result;
	BraseroBurnFlag session_flags;
	BraseroFindLinkCtx ctx = { 0, NULL, 0, };
	BraseroBurnFlag supported_final = BRASERO_BURN_FLAG_NONE;
	BraseroBurnFlag compulsory_final = BRASERO_BURN_FLAG_ALL;


	BRASERO_BURN_LOG_TYPE (output, "Testing temporary image format");

	brasero_caps_find_link_set_ctx (session, &ctx, input);
	ctx.io_flags = BRASERO_PLUGIN_IO_ACCEPT_FILE;


	result = brasero_caps_try_output (self, &ctx, output);
	if (result != BRASERO_BURN_OK) {
		BRASERO_BURN_LOG_TYPE (output, "Format not supported");
		return result;
	}

	session_flags = brasero_burn_session_get_flags (session);


	type_supported = FALSE;
	for (iter = self->priv->caps_list; iter; iter = iter->next) {
		BraseroBurnFlag compulsory;
		BraseroBurnFlag supported;
		BraseroBurnResult result;
		BraseroMedia media;
		BraseroCaps *caps;

		caps = iter->data;
		if (!brasero_track_type_get_has_medium (&caps->type))
			continue;

		media = brasero_track_type_get_medium_type (&caps->type);


		if (media & BRASERO_MEDIUM_ROM)
			continue;

		if ((media & BRASERO_MEDIUM_CD) == 0) {
			if (brasero_track_type_get_has_image (output)) {
				BraseroImageFormat format;

				format = brasero_track_type_get_image_format (output);

				if (format == BRASERO_IMAGE_FORMAT_CDRDAO
				||   format == BRASERO_IMAGE_FORMAT_CLONE
				||   format == BRASERO_IMAGE_FORMAT_CUE)
					continue;
			}
			else if (brasero_track_type_get_has_stream (output))
				continue;
		}


		supported = BRASERO_BURN_FLAG_NONE;
		compulsory = BRASERO_BURN_FLAG_NONE;

		result = brasero_caps_get_flags_for_disc (self,
		                                          brasero_burn_session_get_strict_support (session) == FALSE,
		                                          session_flags,
		                                          media,
							  output,
							  &supported,
							  &compulsory);

		if (result != BRASERO_BURN_OK)
			continue;

		type_supported = TRUE;
		supported_final |= supported;
		compulsory_final &= compulsory;
	}

	BRASERO_BURN_LOG_TYPE (output, "Format supported %i", type_supported);
	if (!type_supported)
		return BRASERO_BURN_NOT_SUPPORTED;

	*supported_ret = supported_final;
	*compulsory_ret = compulsory_final;
	return BRASERO_BURN_OK;
}
