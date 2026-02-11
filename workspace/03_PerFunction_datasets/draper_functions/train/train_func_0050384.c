check_property_domain (TrackerProperty *property)
{
	gint type_index;

	for (type_index = 0; type_index < resource_buffer->types->len; type_index++) {
		if (tracker_property_get_domain (property) == g_ptr_array_index (resource_buffer->types, type_index)) {
			return TRUE;
		}
	}
	return FALSE;
}
