find_contact_source_by_offset (EContactStore *contact_store,
                               gint offset)
{
	GArray *array;
	gint i;

	array = contact_store->priv->contact_sources;

	for (i = 0; i < array->len; i++) {
		ContactSource *source;

		source = &g_array_index (array, ContactSource, i);
		if (source->contacts->len > offset)
			return i;

		offset -= source->contacts->len;
	}

	return -1;
}
