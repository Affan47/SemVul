load_stock_icon (char * id, char * filename,
 GtkIconFactory * iconfactory)
{
    char * path = g_strdup_printf ("%s/images/%s",
     aud_get_path (AUD_PATH_DATA_DIR), filename);

    GdkPixbuf * pixbuf = gdk_pixbuf_new_from_file (path, NULL);
    if (pixbuf == NULL)
        goto ERR;

    GtkIconSet * iconset = gtk_icon_set_new_from_pixbuf(pixbuf);
    g_object_unref(pixbuf);

    gtk_icon_factory_add(iconfactory, id, iconset);

ERR:
    g_free (path);
}
