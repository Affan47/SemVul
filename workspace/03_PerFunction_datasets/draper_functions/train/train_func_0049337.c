nautilus_file_is_date_sort_attribute_q (GQuark attribute_q)
{
	if (attribute_q == attribute_modification_date_q ||
	    attribute_q == attribute_date_modified_q ||
	    attribute_q == attribute_date_modified_full_q ||
	    attribute_q == attribute_accessed_date_q ||
	    attribute_q == attribute_date_accessed_q ||
	    attribute_q == attribute_date_accessed_full_q ||
	    attribute_q == attribute_trashed_on_q ||
	    attribute_q == attribute_trashed_on_full_q) {
		return TRUE;
	}

	return FALSE;
}
