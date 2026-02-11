nautilus_file_get_string_attribute_q (NautilusFile *file, GQuark attribute_q)
{
	char *extension_attribute;

	if (attribute_q == attribute_name_q) {
		return nautilus_file_get_display_name (file);
	}
	if (attribute_q == attribute_type_q) {
		return nautilus_file_get_type_as_string (file);
	}
	if (attribute_q == attribute_detailed_type_q) {
		return nautilus_file_get_detailed_type_as_string (file);
	}
	if (attribute_q == attribute_mime_type_q) {
		return nautilus_file_get_mime_type (file);
	}
	if (attribute_q == attribute_size_q) {
		return nautilus_file_get_size_as_string (file);
	}
	if (attribute_q == attribute_size_detail_q) {
		return nautilus_file_get_size_as_string_with_real_size (file);
	}
	if (attribute_q == attribute_deep_size_q) {
		return nautilus_file_get_deep_size_as_string (file);
	}
	if (attribute_q == attribute_deep_file_count_q) {
		return nautilus_file_get_deep_file_count_as_string (file);
	}
	if (attribute_q == attribute_deep_directory_count_q) {
		return nautilus_file_get_deep_directory_count_as_string (file);
	}
	if (attribute_q == attribute_deep_total_count_q) {
		return nautilus_file_get_deep_total_count_as_string (file);
	}
	if (attribute_q == attribute_trash_orig_path_q) {
		return nautilus_file_get_trash_original_file_parent_as_string (file);
	}
	if (attribute_q == attribute_date_modified_q) {
		return nautilus_file_get_date_as_string (file,
							 NAUTILUS_DATE_TYPE_MODIFIED,
							 TRUE);
	}
	if (attribute_q == attribute_date_modified_full_q) {
		return nautilus_file_get_date_as_string (file,
							 NAUTILUS_DATE_TYPE_MODIFIED,
							 FALSE);
	}
	if (attribute_q == attribute_date_accessed_q) {
		return nautilus_file_get_date_as_string (file,
							 NAUTILUS_DATE_TYPE_ACCESSED,
							 TRUE);
	}
	if (attribute_q == attribute_date_accessed_full_q) {
		return nautilus_file_get_date_as_string (file,
							 NAUTILUS_DATE_TYPE_ACCESSED,
							 FALSE);
	}
	if (attribute_q == attribute_trashed_on_q) {
		return nautilus_file_get_date_as_string (file,
							 NAUTILUS_DATE_TYPE_TRASHED,
							 TRUE);
	}
	if (attribute_q == attribute_trashed_on_full_q) {
		return nautilus_file_get_date_as_string (file,
							 NAUTILUS_DATE_TYPE_TRASHED,
							 FALSE);
	}
	if (attribute_q == attribute_permissions_q) {
		return nautilus_file_get_permissions_as_string (file);
	}
	if (attribute_q == attribute_selinux_context_q) {
		return nautilus_file_get_selinux_context (file);
	}
	if (attribute_q == attribute_octal_permissions_q) {
		return nautilus_file_get_octal_permissions_as_string (file);
	}
	if (attribute_q == attribute_owner_q) {
		return nautilus_file_get_owner_as_string (file, TRUE);
	}
	if (attribute_q == attribute_group_q) {
		return nautilus_file_get_group_name (file);
	}
	if (attribute_q == attribute_uri_q) {
		return nautilus_file_get_uri (file);
	}
	if (attribute_q == attribute_where_q) {
		return nautilus_file_get_where_string (file);
	}
	if (attribute_q == attribute_link_target_q) {
		return nautilus_file_get_symbolic_link_target_path (file);
	}
	if (attribute_q == attribute_volume_q) {
		return nautilus_file_get_volume_name (file);
	}
	if (attribute_q == attribute_free_space_q) {
		return nautilus_file_get_volume_free_space (file);
	}

	extension_attribute = NULL;

	if (file->details->pending_extension_attributes) {
		extension_attribute = g_hash_table_lookup (file->details->pending_extension_attributes,
							   GINT_TO_POINTER (attribute_q));
	}

	if (extension_attribute == NULL && file->details->extension_attributes) {
		extension_attribute = g_hash_table_lookup (file->details->extension_attributes,
							   GINT_TO_POINTER (attribute_q));
	}

	return g_strdup (extension_attribute);
}
