image_write(gpaint_image* image, const gchar* filename, GError **perror)
{
    gboolean saved = FALSE;
    gchar *ext = NULL;
    gchar *type = NULL;

    GSList *formats = gdk_pixbuf_get_formats ();
    GSList *writable_formats = NULL;
    g_slist_foreach (formats, add_if_writable, &writable_formats);
    g_slist_free (formats);

    ext = g_strrstr(filename, ".");
    if (!ext)
    {
       ext = ".png";
    }
    debug1("extension=[%s]", ext);

    if (!g_strcasecmp(ext,".jpg") || !g_strcasecmp(ext,".jpeg"))
    {
        debug("saving jpeg");
        saved = gdk_pixbuf_save(image->pixbuf, filename, "jpeg", perror, "quality", "100", NULL);
    }
    else
    {
        type = g_ascii_strdown(ext+1,-1);
        debug1("type=[%s]",type);
        if (is_writable (writable_formats, type))
        {
            saved = gdk_pixbuf_save(image->pixbuf, filename, type, perror, NULL);
        } else {
            saved = FALSE;
            *perror = g_error_new (GDK_PIXBUF_ERROR, GDK_PIXBUF_ERROR_BAD_OPTION, _("Saving in the '%s' format is not supported by gdk_pixbuf"), type);
        }
        g_free(type);
    }
    if (!saved && *perror)
    {
        g_warning("Could not save image %s: %s\n", filename, (*perror)->message);
    }
	g_slist_free (writable_formats);
    return saved;
}
