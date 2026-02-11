find_wrapper (MonoMethod *m, gint no, gint ilo, gboolean managed, gpointer data)
{
	if (managed)
		return TRUE;

	if (mono_threads_is_critical_method (m)) {
		*((gboolean*)data) = TRUE;
		return TRUE;
	}
	return FALSE;
}
