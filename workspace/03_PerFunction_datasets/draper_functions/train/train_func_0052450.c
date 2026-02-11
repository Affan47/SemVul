nautilus_view_supports_creating_files (NautilusView *view)
{
	g_return_val_if_fail (NAUTILUS_IS_VIEW (view), FALSE);

	return !nautilus_view_is_read_only (view)
		&& !showing_trash_directory (view)
		&& !showing_recent_directory (view);
}
