mono_string_to_utf32 (MonoString *s)
{
	MONO_REQ_GC_UNSAFE_MODE;

	mono_unichar4 *utf32_output = NULL;
	GError *error = NULL;
	glong items_written;

	if (s == NULL)
		return NULL;

	utf32_output = g_utf16_to_ucs4 (s->chars, s->length, NULL, &items_written, &error);

	if (error)
		g_error_free (error);

	return utf32_output;
}
