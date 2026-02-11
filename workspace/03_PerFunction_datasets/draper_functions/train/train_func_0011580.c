mono_exception_get_managed_backtrace (MonoException *exc)
{
	GString *text;

	text = g_string_new_len (NULL, 20);

	if (!mono_get_eh_callbacks ()->mono_exception_walk_trace (exc, append_frame_and_continue, text))
		g_string_append (text, "managed backtrace not available\n");

	return g_string_free (text, FALSE);
}
