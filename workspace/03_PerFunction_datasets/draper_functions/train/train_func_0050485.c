g_mime_part_finalize (GObject *object)
{
	GMimePart *mime_part = (GMimePart *) object;

	g_free (mime_part->content_description);
	g_free (mime_part->content_location);
	g_free (mime_part->content_md5);

	if (mime_part->content)
		g_object_unref (mime_part->content);

	G_OBJECT_CLASS (parent_class)->finalize (object);
}
