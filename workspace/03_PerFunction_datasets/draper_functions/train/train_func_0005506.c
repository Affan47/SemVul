view_state_changed (ChamplainView *view,
    GParamSpec *gobject,
    GtkImage *image)
{
  ChamplainState state;

  if (destroying)
    return;

  g_object_get (G_OBJECT (view), "state", &state, NULL);
  if (state == CHAMPLAIN_STATE_LOADING)
    {
      gtk_image_set_from_stock (image, GTK_STOCK_NETWORK, GTK_ICON_SIZE_BUTTON);
    }
  else
    {
      gtk_image_clear (image);
    }
}
