focusblur_stock_update_modelbrush (const gchar *brush_name)
{
  GtkIconSet *set;
  GdkPixbuf  *pixbuf;

  g_return_if_fail (fblur_stock_factory != NULL);

  pixbuf = focusblur_pixbuf_new_from_gimp_brush (brush_name);
  set = gtk_icon_set_new_from_pixbuf (pixbuf);
  gtk_icon_factory_add (fblur_stock_factory, FBLUR_STOCK_MODEL_BRUSH, set);

  gtk_icon_set_unref (set);
  g_object_unref (pixbuf);
}
