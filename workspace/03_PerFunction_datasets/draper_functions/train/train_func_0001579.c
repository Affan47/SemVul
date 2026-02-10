egg_list_box_update_active (EggListBox *list_box, EggListBoxChildInfo *child)
{
  EggListBoxPrivate *priv = list_box->priv;
  gboolean val;

  val = priv->active_child == child;
  if (priv->active_child != NULL &&
      val != priv->active_child_active)
    {
      priv->active_child_active = val;
      gtk_widget_queue_draw (GTK_WIDGET (list_box));
    }
}
