mono_memberref_is_method (MonoImage *image, guint32 token)
{
	if (!image_is_dynamic (image)) {
		guint32 cols [MONO_MEMBERREF_SIZE];
		const char *sig;
		mono_metadata_decode_row (&image->tables [MONO_TABLE_MEMBERREF], mono_metadata_token_index (token) - 1, cols, MONO_MEMBERREF_SIZE);
		sig = mono_metadata_blob_heap (image, cols [MONO_MEMBERREF_SIGNATURE]);
		mono_metadata_decode_blob_size (sig, &sig);
		return (*sig != 0x6);
	} else {
		MonoClass *handle_class;

		if (!mono_lookup_dynamic_token_class (image, token, FALSE, &handle_class, NULL))
			return FALSE;

		return mono_defaults.methodhandle_class == handle_class;
	}
}
