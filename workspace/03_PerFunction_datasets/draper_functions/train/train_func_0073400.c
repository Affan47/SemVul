egg_list_box_real_drag_leave (GtkWidget *widget, GdkDragContext *context, guint time_)
{
  EggListBox *list_box = EGG_LIST_BOX (widget);
  EggListBoxPrivate *priv = list_box->priv;

  egg_list_box_drag_unhighlight_widget (list_box);
  if (priv->auto_scroll_timeout_id != 0) {
    g_source_remove (priv->auto_scroll_timeout_id);
    priv->auto_scroll_timeout_id = 0;
  }
}
