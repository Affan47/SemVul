inf_text_gtk_view_set_view(InfTextGtkView* view,
                           GtkTextView* gtk_view)
{
  InfTextGtkViewPrivate* priv;
  priv = INF_TEXT_GTK_VIEW_PRIVATE(view);

  if(priv->textview != NULL)
  {
    inf_signal_handlers_disconnect_by_func(
      G_OBJECT(priv->textview),
#if GTK_CHECK_VERSION(2, 91, 0)
      G_CALLBACK(inf_text_gtk_view_draw_before_cb),
#else
      G_CALLBACK(inf_text_gtk_view_expose_event_before_cb),
#endif
      view
    );

    inf_signal_handlers_disconnect_by_func(
      G_OBJECT(priv->textview),
#if GTK_CHECK_VERSION(2, 91, 0)
      G_CALLBACK(inf_text_gtk_view_draw_after_cb),
#else
      G_CALLBACK(inf_text_gtk_view_expose_event_after_cb),
#endif
      view
    );

    inf_signal_handlers_disconnect_by_func(
      G_OBJECT(priv->textview),
      G_CALLBACK(inf_text_gtk_view_style_set_cb),
      view
    );

    inf_signal_handlers_disconnect_by_func(
      G_OBJECT(priv->textview),
      G_CALLBACK(inf_text_gtk_view_size_allocate_cb),
      view
    );

    g_object_unref(priv->textview);
  }

  priv->textview = gtk_view;

  if(gtk_view != NULL)
  {
    g_object_ref(gtk_view);

    g_signal_connect(
      G_OBJECT(gtk_view),
#if GTK_CHECK_VERSION(2, 91, 0)
      "draw",
      G_CALLBACK(inf_text_gtk_view_draw_before_cb),
#else
      "expose-event",
      G_CALLBACK(inf_text_gtk_view_expose_event_before_cb),
#endif
      view
    );

    g_signal_connect_after(
      G_OBJECT(gtk_view),
#if GTK_CHECK_VERSION(2, 91, 0)
      "draw",
      G_CALLBACK(inf_text_gtk_view_draw_after_cb),
#else
      "expose-event",
      G_CALLBACK(inf_text_gtk_view_expose_event_after_cb),
#endif
      view
    );

    g_signal_connect_after(
      G_OBJECT(gtk_view),
      "style-set",
      G_CALLBACK(inf_text_gtk_view_style_set_cb),
      view
    );


    g_signal_connect_after(
      G_OBJECT(gtk_view),
      "size-allocate",
      G_CALLBACK(inf_text_gtk_view_size_allocate_cb),
      view
    );
  }

  g_object_notify(G_OBJECT(view), "view");
}
