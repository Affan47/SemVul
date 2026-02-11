gtv_do_resize (GtkVideo *gtv, const GtkRequisition *size)
{
  gtk_widget_set_size_request (&gtv->widget, size->width, size->height);
  if (GTK_WIDGET_REALIZED(&gtv->widget) && gtv->widget.parent)
  {
    GdkGeometry geom;
    GtkWindow *toplevel = GTK_WINDOW (gtk_widget_get_toplevel (&gtv->widget));
    if (toplevel->bin.child == &gtv->widget)
    {
      geom.min_width = size->width;
      geom.min_height = size->height;
      gtk_window_set_geometry_hints (toplevel, &gtv->widget, &geom,
				     GDK_HINT_MIN_SIZE);
    }
    gtk_window_resize ((GtkWindow *)gtk_widget_get_toplevel (&gtv->widget),
		       size->width, size->height);
    if (toplevel->bin.child == &gtv->widget)
    {
      geom.min_aspect = geom.max_aspect = (double)size->width / (double)size->height;
      gtk_window_set_geometry_hints (toplevel, &gtv->widget, &geom,
				     GDK_HINT_ASPECT);
    }
    gtk_video_allow_shrink (gtv);
  }
}
