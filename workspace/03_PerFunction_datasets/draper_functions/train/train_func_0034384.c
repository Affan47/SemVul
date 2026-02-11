mx_scroll_view_actor_removed (ClutterContainer *container,
                              ClutterActor     *actor)
{
  MxScrollViewPrivate *priv = MX_SCROLL_VIEW (container)->priv;

  if (actor == priv->child)
    {
      g_object_ref (priv->child);

      g_signal_handlers_disconnect_by_func (priv->child,
                                            child_hadjustment_notify_cb,
                                            container);
      g_signal_handlers_disconnect_by_func (priv->child,
                                            child_vadjustment_notify_cb,
                                            container);
      mx_scrollable_set_adjustments ((MxScrollable*) priv->child, NULL, NULL);

      g_object_unref (priv->child);
      priv->child = NULL;
    }
}
