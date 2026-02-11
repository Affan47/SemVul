glade_widget_unlock (GladeWidget * widget)
{
  GladeWidget *lock;

  g_return_if_fail (GLADE_IS_WIDGET (widget));
  g_return_if_fail (GLADE_IS_WIDGET (widget->priv->lock));

  lock = widget->priv->lock;

  lock->priv->locked_widgets =
    g_list_remove (lock->priv->locked_widgets, widget);

  widget->priv->lock = NULL;
}
