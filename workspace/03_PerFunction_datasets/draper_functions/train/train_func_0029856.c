on_inspector_show_window (WebKitWebInspector *inspector,
                          GwhBrowser         *self)
{
  gtk_widget_show (self->priv->inspector_view);
  if (INSPECTOR_DETACHED (self)) {
    inspector_show_window (self);
  }
  gtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (self->priv->item_inspector),
                                     TRUE);

  return TRUE;
}
