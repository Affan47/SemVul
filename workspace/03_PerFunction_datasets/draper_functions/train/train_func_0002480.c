new_pixbuf_from_widget (GtkWidget *widget)
{
  GtkWidget *window;
  GdkPixbuf *pixbuf;
  GtkRequisition requisition;
  GtkAllocation allocation;
  GdkPixmap *pixmap;
  gint icon_width;
  gint icon_height;

#define DEFAULT_ICON_HEIGHT 20
#define DEFAULT_ICON_WIDTH 0

  icon_width = DEFAULT_ICON_WIDTH;

  if (!gtk_icon_size_lookup_for_settings (gtk_settings_get_default (),
                                          GTK_ICON_SIZE_LARGE_TOOLBAR,
                                          NULL, &icon_height))
    {
      icon_height = DEFAULT_ICON_HEIGHT;
    }

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_container_add (GTK_CONTAINER (window), widget);
  gtk_widget_realize (window);
  gtk_widget_show (widget);
  gtk_widget_realize (widget);
  gtk_widget_map (widget);


  gtk_window_set_default_size (GTK_WINDOW (window), icon_width, icon_height);
  gtk_window_get_size (GTK_WINDOW (window),&icon_width, &icon_height);

  gtk_widget_size_request (window, &requisition);
  allocation.x = 0;
  allocation.y = 0;
  allocation.width = icon_width;
  allocation.height = icon_height;
  gtk_widget_size_allocate (window, &allocation);
  gtk_widget_size_request (window, &requisition);


  pixmap = gdk_pixmap_new (GDK_DRAWABLE (window->window), icon_width, icon_height, -1);
  gdk_drawable_set_colormap (GDK_DRAWABLE (pixmap), gtk_widget_get_colormap (window));


  gtk_widget_ensure_style (window);
  g_assert (window->style);
  g_assert (window->style->font_desc);

  fake_expose_widget (window, pixmap);
  fake_expose_widget (widget, pixmap);

  pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, TRUE, 8, icon_width, icon_height);
  gdk_pixbuf_get_from_drawable (pixbuf, pixmap, NULL, 0, 0, 0, 0, icon_width, icon_height);

  return pixbuf;
}
