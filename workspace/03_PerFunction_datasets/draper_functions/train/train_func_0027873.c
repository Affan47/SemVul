sigcont_dispatch(GSource *source, GSourceFunc callback, gpointer user_data)
{
	got_sigcont = FALSE;
	if (callback == NULL)
		return TRUE;
	return callback(user_data);
}
