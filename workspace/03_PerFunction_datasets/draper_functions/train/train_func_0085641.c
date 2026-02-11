on_button_hierarchy_changed (GtkWidget* widget,
			     GtkWidget* old_toplevel,
			     gpointer data)
{
  GmSmileyChooserButton* self = NULL;
  GtkWidget* new_toplevel = NULL;

  g_return_if_fail (data != NULL && GM_IS_SMILEY_CHOOSER_BUTTON (data));

  self = GM_SMILEY_CHOOSER_BUTTON (data);

  if (old_toplevel &&
      self->priv->toplevel_window_handler[HANDLER_CONFIGURE]) {

      g_signal_handler_disconnect (G_OBJECT (old_toplevel),
				   self->priv->toplevel_window_handler[HANDLER_CONFIGURE]);
      self->priv->toplevel_window_handler[HANDLER_CONFIGURE] = 0;
    }

  if (old_toplevel &&
      self->priv->toplevel_window_handler[HANDLER_SCREEN_CHANGED]) {

      g_signal_handler_disconnect (G_OBJECT (old_toplevel),
				   self->priv->toplevel_window_handler[HANDLER_SCREEN_CHANGED]);
      self->priv->toplevel_window_handler[HANDLER_SCREEN_CHANGED] = 0;
    }

  if (old_toplevel &&
      self->priv->toplevel_window_handler[HANDLER_HIDE]) {

      g_signal_handler_disconnect (G_OBJECT (old_toplevel),
				   self->priv->toplevel_window_handler[HANDLER_HIDE]);
      self->priv->toplevel_window_handler[HANDLER_HIDE] = 0;
    }

  if (old_toplevel &&
      self->priv->toplevel_window_handler[HANDLER_DELETE_EVENT]) {

      g_signal_handler_disconnect (G_OBJECT (old_toplevel),
				   self->priv->toplevel_window_handler[HANDLER_DELETE_EVENT]);
      self->priv->toplevel_window_handler[HANDLER_DELETE_EVENT] = 0;
    }

  if (old_toplevel) {

      gtk_window_set_transient_for (GTK_WINDOW (self->priv->popup_window), NULL);
      g_object_unref (G_OBJECT (old_toplevel));
    }

  new_toplevel = gtk_widget_get_toplevel (widget);

  if (GTK_IS_WINDOW (new_toplevel)) {

      g_object_ref_sink (G_OBJECT (new_toplevel));
      self->priv->toplevel_window_handler[HANDLER_CONFIGURE] =
	g_signal_connect (new_toplevel, "configure-event",
			  G_CALLBACK (on_toplevel_configure_event), self);
      self->priv->toplevel_window_handler[HANDLER_SCREEN_CHANGED] =
	g_signal_connect (new_toplevel, "screen-changed",
			  G_CALLBACK (on_toplevel_screen_changed), self);
      self->priv->toplevel_window_handler[HANDLER_HIDE] =
	g_signal_connect (new_toplevel, "hide",
			  G_CALLBACK (on_toplevel_hide), self);
      self->priv->toplevel_window_handler[HANDLER_DELETE_EVENT] =
	g_signal_connect (new_toplevel, "delete-event",
			  G_CALLBACK (on_toplevel_delete_event), self);
      gtk_window_set_transient_for (GTK_WINDOW (self->priv->popup_window),
				    GTK_WINDOW (new_toplevel));
    }
}
