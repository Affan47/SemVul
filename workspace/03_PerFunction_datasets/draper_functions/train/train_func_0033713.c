focusblur_stock_init (void)
{
  GtkIconSet    *set;
  GdkPixbuf     *pixbuf;
  gint           i;

  if (fblur_stock_factory)
    return;

  fblur_stock_factory = gtk_icon_factory_new ();

  for (i = 0; i < G_N_ELEMENTS (fblur_stock_pixbufs); i++)
    {
      pixbuf =
        gdk_pixbuf_from_pixdata (fblur_stock_pixbufs[i].pixdata, TRUE, NULL);
      g_assert (pixbuf != NULL);

      set = gtk_icon_set_new_from_pixbuf (pixbuf);
      gtk_icon_factory_add
        (fblur_stock_factory, fblur_stock_pixbufs[i].stock_id, set);

      gtk_icon_set_unref (set);
      g_object_unref (pixbuf);
    }


  focusblur_stock_update_modelbrush (NULL);

  gtk_icon_factory_add_default (fblur_stock_factory);
  gtk_stock_add_static (fblur_stock_items, G_N_ELEMENTS (fblur_stock_items));
}
