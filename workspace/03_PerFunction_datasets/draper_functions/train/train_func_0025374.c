brasero_burn_caps_get_blanking_flags_real (BraseroBurnCaps *caps,
                                           gboolean ignore_errors,
					   BraseroMedia media,
					   BraseroBurnFlag session_flags,
					   BraseroBurnFlag *supported,
					   BraseroBurnFlag *compulsory)
{
	GSList *iter;
	gboolean supported_media;
	BraseroBurnFlag supported_flags = BRASERO_BURN_FLAG_NONE;
	BraseroBurnFlag compulsory_flags = BRASERO_BURN_FLAG_ALL;

	BRASERO_BURN_LOG_DISC_TYPE (media, "Getting blanking flags for");
	if (media == BRASERO_MEDIUM_NONE) {
		BRASERO_BURN_LOG ("Blanking not possible: no media");
		if (supported)
			*supported = BRASERO_BURN_FLAG_NONE;
		if (compulsory)
			*compulsory = BRASERO_BURN_FLAG_NONE;
		return BRASERO_BURN_NOT_SUPPORTED;
	}

	supported_media = FALSE;
	for (iter = caps->priv->caps_list; iter; iter = iter->next) {
		BraseroMedia caps_media;
		BraseroCaps *caps;
		GSList *links;

		caps = iter->data;
		if (!brasero_track_type_get_has_medium (&caps->type))
			continue;

		caps_media = brasero_track_type_get_medium_type (&caps->type);
		if ((media & caps_media) != media)
			continue;

		for (links = caps->links; links; links = links->next) {
			GSList *plugins;
			BraseroCapsLink *link;

			link = links->data;

			if (link->caps != NULL)
				continue;

			supported_media = TRUE;


			for (plugins = link->plugins; plugins; plugins = plugins->next) {
				BraseroPlugin *plugin;
				BraseroBurnFlag supported_plugin;
				BraseroBurnFlag compulsory_plugin;

				plugin = plugins->data;
				if (!brasero_plugin_get_active (plugin, ignore_errors))
					continue;

				if (!brasero_plugin_get_blank_flags (plugin,
								     media,
								     session_flags,
								     &supported_plugin,
								     &compulsory_plugin))
					continue;

				supported_flags |= supported_plugin;
				compulsory_flags &= compulsory_plugin;
			}
		}
	}

	if (!supported_media) {
		BRASERO_BURN_LOG ("media blanking not supported");
		return BRASERO_BURN_NOT_SUPPORTED;
	}


	if (BRASERO_MEDIUM_IS (media, BRASERO_MEDIUM_DVDRW)
	&& (session_flags & BRASERO_BURN_FLAG_MULTI)) {
		if (compulsory_flags & BRASERO_BURN_FLAG_FAST_BLANK) {
			BRASERO_BURN_LOG ("fast media blanking only supported but multisession required for DVDRW");
			return BRASERO_BURN_NOT_SUPPORTED;
		}

		supported_flags &= ~BRASERO_BURN_FLAG_FAST_BLANK;

		BRASERO_BURN_LOG ("removed fast blank for a DVDRW with multisession");
	}

	if (supported)
		*supported = supported_flags;
	if (compulsory)
		*compulsory = compulsory_flags;

	return BRASERO_BURN_OK;
}
