mono_image_check_for_module_cctor (MonoImage *image)
{
	MonoTableInfo *t, *mt;
	t = &image->tables [MONO_TABLE_TYPEDEF];
	mt = &image->tables [MONO_TABLE_METHOD];
	if (image_is_dynamic (image)) {

		image->checked_module_cctor = TRUE;
		return;
	}
	if (t->rows >= 1) {
		guint32 nameidx = mono_metadata_decode_row_col (t, 0, MONO_TYPEDEF_NAME);
		const char *name = mono_metadata_string_heap (image, nameidx);
		if (strcmp (name, "<Module>") == 0) {
			guint32 first_method = mono_metadata_decode_row_col (t, 0, MONO_TYPEDEF_METHOD_LIST) - 1;
			guint32 last_method;
			if (t->rows > 1)
				last_method = mono_metadata_decode_row_col (t, 1, MONO_TYPEDEF_METHOD_LIST) - 1;
			else
				last_method = mt->rows;
			for (; first_method < last_method; first_method++) {
				nameidx = mono_metadata_decode_row_col (mt, first_method, MONO_METHOD_NAME);
				name = mono_metadata_string_heap (image, nameidx);
				if (strcmp (name, ".cctor") == 0) {
					image->has_module_cctor = TRUE;
					image->checked_module_cctor = TRUE;
					return;
				}
			}
		}
	}
	image->has_module_cctor = FALSE;
	image->checked_module_cctor = TRUE;
}
