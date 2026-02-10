gtk_text_region_new (GtkTextBuffer *buffer)
{
	GtkTextRegion *region;

	g_return_val_if_fail (GTK_IS_TEXT_BUFFER (buffer), NULL);

	region = g_new (GtkTextRegion, 1);
	region->subregions = NULL;
	region->time_stamp = 0;

	region->buffer = buffer;

	g_object_add_weak_pointer (G_OBJECT (buffer),
				   (gpointer *)&region->buffer);

	return region;
}
