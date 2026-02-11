nemo_bookmark_finalize (GObject *object)
{
	NemoBookmark *bookmark;

	g_assert (NEMO_IS_BOOKMARK (object));

	bookmark = NEMO_BOOKMARK (object);

	nemo_bookmark_disconnect_file (bookmark);

	g_object_unref (bookmark->details->location);
	g_clear_object (&bookmark->details->icon);

	g_free (bookmark->details->name);
	g_free (bookmark->details->scroll_file);

	G_OBJECT_CLASS (nemo_bookmark_parent_class)->finalize (object);
}
