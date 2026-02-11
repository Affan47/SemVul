gtk_clutter_embed_size_allocate (GtkWidget     *widget,
                                 GtkAllocation *allocation)
{
  GtkClutterEmbedPrivate *priv = GTK_CLUTTER_EMBED (widget)->priv;
  int scale_factor = gtk_widget_get_scale_factor (widget);

  gtk_widget_set_allocation (widget, allocation);


  clutter_actor_set_size (priv->stage, allocation->width * scale_factor, allocation->height * scale_factor);

  if (gtk_widget_get_realized (widget))
    {
      gdk_window_move_resize (gtk_widget_get_window (widget),
                              allocation->x,
                              allocation->y,
                              allocation->width,
                              allocation->height);

      clutter_stage_ensure_viewport (CLUTTER_STAGE (priv->stage));

      gtk_clutter_embed_send_configure (GTK_CLUTTER_EMBED (widget));

#if defined(GDK_WINDOWING_X11) && defined(CLUTTER_WINDOWING_X11)
      if (clutter_check_windowing_backend (CLUTTER_WINDOWING_X11) &&
	  GDK_IS_X11_WINDOW (gtk_widget_get_window (widget)))
	{
	  XConfigureEvent xevent = { ConfigureNotify };
	  xevent.window = GDK_WINDOW_XID (gtk_widget_get_window (widget));
	  xevent.width = allocation->width * scale_factor;
	  xevent.height = allocation->height * scale_factor;


	  clutter_x11_handle_event ((XEvent *)&xevent);
	}
#endif
    }
}
