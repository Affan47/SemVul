mono_metadata_parse_typedef_or_ref (MonoImage *m, const char *ptr, const char **rptr)
{
	guint32 token;
	token = mono_metadata_decode_value (ptr, &ptr);
	if (rptr)
		*rptr = ptr;
	return mono_metadata_token_from_dor (token);
}
