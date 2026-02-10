nautilus_file_get_string_attribute_with_default_q (NautilusFile *file, GQuark attribute_q)
{
	char *result;
	guint item_count;
	gboolean count_unreadable;
	NautilusRequestStatus status;

	result = nautilus_file_get_string_attribute_q (file, attribute_q);
	if (result != NULL) {
		return result;
	}


	if (attribute_q == attribute_size_q) {
		if (!nautilus_file_should_show_directory_item_count (file)) {
			return g_strdup ("--");
		}
		count_unreadable = FALSE;
		if (nautilus_file_is_directory (file)) {
			nautilus_file_get_directory_item_count (file, &item_count, &count_unreadable);
		}
		return g_strdup (count_unreadable ? _("? items") : "...");
	}
	if (attribute_q == attribute_deep_size_q) {
		status = nautilus_file_get_deep_counts (file, NULL, NULL, NULL, NULL, FALSE);
		if (status == NAUTILUS_REQUEST_DONE) {

			return g_strdup (_("? bytes"));
		}
		return g_strdup ("...");
	}
	if (attribute_q == attribute_deep_file_count_q
	    || attribute_q == attribute_deep_directory_count_q
	    || attribute_q == attribute_deep_total_count_q) {
		status = nautilus_file_get_deep_counts (file, NULL, NULL, NULL, NULL, FALSE);
		if (status == NAUTILUS_REQUEST_DONE) {

			return g_strdup (_("? items"));
		}
		return g_strdup ("...");
	}
	if (attribute_q == attribute_type_q
	    || attribute_q == attribute_detailed_type_q
	    || attribute_q == attribute_mime_type_q) {
		return g_strdup (_("Unknown"));
	}
	if (attribute_q == attribute_trashed_on_q) {

		return g_strdup ("");
	}
	if (attribute_q == attribute_trash_orig_path_q) {

		return g_strdup ("");
	}


	return g_strdup (_("unknown"));
}
