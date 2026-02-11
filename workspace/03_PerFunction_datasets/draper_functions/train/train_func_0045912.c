tag_iterate (const GstTagList *list,
	     const char       *tag,
	     GFileInfo        *info)
{
	const char *tag_key;
	char       *attribute = NULL;

	tag_key = NULL;

	if (strcmp (tag, "container-format") == 0) {
		tag_key = "general::format";
	}
	else if (strcmp (tag, "bitrate") == 0) {
		tag_key = "audio-video::general::bitrate";
	}
	else if (strcmp (tag, "encoder") == 0) {
		tag_key = "audio-video::general::encoder";
	}
	else if (strcmp (tag, "title") == 0) {
		tag_key = "general::title";
	}
	else if (strcmp (tag, "artist") == 0) {
		tag_key = "audio-video::general::artist";
	}
	else if (strcmp (tag, "album") == 0) {
		tag_key = "audio-video::general::album";
	}
	else if (strcmp (tag, "audio-codec") == 0) {
		tag_key = "audio-video::audio::codec";
	}
	else if (strcmp (tag, "video-codec") == 0) {
		tag_key = "audio-video::video::codec";
	}

	if (tag_key == NULL) {
		GthMetadataInfo *metadata_info;

		attribute = g_strconcat ("audio-video::other::", tag, NULL);
		metadata_info = gth_main_get_metadata_info (attribute);
		if (metadata_info == NULL) {
			GthMetadataInfo *info;

			info = g_new0 (GthMetadataInfo, 1);
			info->id = attribute;
			info->display_name = gst_tag_get_nick (tag);
			info->category = "audio-video::other";
			info->sort_order = 500;
			info->flags = GTH_METADATA_ALLOW_IN_PROPERTIES_VIEW;
			metadata_info = gth_main_register_metadata_info (info);

			g_free (info);
		}

		tag_key = attribute;
	}

	add_metadata_from_tag (info, list, tag, tag_key);

	g_free (attribute);
}
