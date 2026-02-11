on_web_view_leave_notify_event (GtkWidget        *widget,
                                GdkEventCrossing *event,
                                GwhBrowser       *self)
{
  if (self->priv->hovered_link) {
    GtkStatusbar *statusbar = GTK_STATUSBAR (self->priv->statusbar);

    gtk_statusbar_pop (statusbar, get_statusbar_context_id (statusbar));
  }
}
