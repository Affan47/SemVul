register_stock_icon (GtkIconFactory *factory,
                     const gchar *stock_id,
                     const gchar *icon_name,
                     const gchar *file_name,
                     GtkIconSize size)
{
  GtkIconTheme *icon_theme = gtk_icon_theme_get_default ();
  GdkPixbuf *pixbuf;
  GtkIconInfo *info;
  gint w, h;

  if (gtk_icon_size_lookup (size, &w, &h) &&
      (info = gtk_icon_theme_lookup_icon (icon_theme, icon_name, MIN (w, h), 0)))
    {
      pixbuf = gtk_icon_info_load_icon (info, NULL);
    }
  else
    {
      gchar *path = g_build_filename (glade_app_get_pixmaps_dir (), file_name, NULL);
      pixbuf = gdk_pixbuf_new_from_file (path, NULL);
      g_free (path);
    }

  if (pixbuf)
    {
      GtkIconSet *icon_set = gtk_icon_set_new_from_pixbuf (pixbuf);
      gtk_icon_factory_add (factory, stock_id, icon_set);
      g_object_unref (pixbuf);
    }
}
