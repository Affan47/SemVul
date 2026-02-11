_gdk_pixbuf_get_module_for_file (FILE *f, const gchar *filename, GError **error)
{
        guchar buffer[SNIFF_BUFFER_SIZE];
        int size;

        size = fread (&buffer, 1, sizeof (buffer), f);
        if (size == 0) {
		gchar *display_name;
        	display_name = g_filename_display_name (filename);
                g_set_error (error,
                             GDK_PIXBUF_ERROR,
                             GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
                             _("Image file '%s' contains no data"),
                             display_name);
                g_free (display_name);
                return NULL;
        }

	return _gdk_pixbuf_get_module (buffer, size, filename, error);
}
