mnote_canon_entry_count_values (const MnoteCanonEntry *entry)
{
	unsigned int  val;

	if (!entry) return 0;

	switch (entry->tag) {
	case MNOTE_CANON_TAG_FOCAL_LENGTH:
	case MNOTE_CANON_TAG_PANORAMA:
		return entry->components;
	case MNOTE_CANON_TAG_SETTINGS_1:
	case MNOTE_CANON_TAG_SETTINGS_2:
	case MNOTE_CANON_TAG_CUSTOM_FUNCS:
	case MNOTE_CANON_TAG_COLOR_INFORMATION:
		if (entry->format != EXIF_FORMAT_SHORT) return 0;

		val = exif_get_short (entry->data, entry->order);

		return MIN (entry->size - 2, val) / 2;
	default:
		return 1;
	}
}
