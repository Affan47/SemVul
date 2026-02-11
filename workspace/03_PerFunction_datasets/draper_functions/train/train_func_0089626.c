tpaw_irc_network_chooser_dialog_dispose (GObject *object)
{
  TpawIrcNetworkChooserDialog *self = (TpawIrcNetworkChooserDialog *) object;

  if (self->priv->search_sig != 0)
    {
      g_signal_handler_disconnect (self->priv->search,
          self->priv->search_sig);
      self->priv->search_sig = 0;
    }

  if (self->priv->activate_sig != 0)
    {
      g_signal_handler_disconnect (self->priv->search,
          self->priv->activate_sig);
      self->priv->activate_sig = 0;
    }

  if (self->priv->search != NULL)
    {
      tpaw_live_search_set_hook_widget (
          TPAW_LIVE_SEARCH (self->priv->search), NULL);

      self->priv->search = NULL;
    }

  tp_clear_object (&self->priv->settings);
  tp_clear_object (&self->priv->network);
  tp_clear_object (&self->priv->network_manager);
  tp_clear_object (&self->priv->store);
  tp_clear_object (&self->priv->filter);

  if (G_OBJECT_CLASS (tpaw_irc_network_chooser_dialog_parent_class)->dispose)
    G_OBJECT_CLASS (tpaw_irc_network_chooser_dialog_parent_class)->dispose (object);
}
