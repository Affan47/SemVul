on_web_view_scroll_event (GtkWidget      *widget,
                          GdkEventScroll *event,
                          GwhBrowser     *self)
{
  guint     mods = event->state & gtk_accelerator_get_default_mod_mask ();
  gboolean  handled = FALSE;

  if (mods == GDK_CONTROL_MASK) {
    handled = TRUE;
    switch (event->direction) {
      case GDK_SCROLL_DOWN:
        webkit_web_view_zoom_out (WEBKIT_WEB_VIEW (self->priv->web_view));
        break;

      case GDK_SCROLL_UP:
        webkit_web_view_zoom_in (WEBKIT_WEB_VIEW (self->priv->web_view));
        break;

      default:
        handled = FALSE;
    }
  }

  return handled;
}
