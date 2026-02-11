gtk_meta_destroy (GtkObject *object)
{
	GtkMeta *meta;

	g_return_if_fail (object != NULL);
	g_return_if_fail (GTK_IS_META (object));

	meta = GTK_META (object);

	g_free(meta->colors);

	gdk_cursor_destroy(meta->cursor);

	gdk_font_unref (meta->font);


	if (GTK_OBJECT_CLASS (parent_class)->destroy)
		(* GTK_OBJECT_CLASS (parent_class)->destroy)(object);
}
