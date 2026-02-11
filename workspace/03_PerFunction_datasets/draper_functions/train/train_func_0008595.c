tp_channel_manager_foreach_channel (TpChannelManager *manager,
                                    TpExportableChannelFunc func,
                                    gpointer user_data)
{
  TpChannelManagerIface *iface = TP_CHANNEL_MANAGER_GET_INTERFACE (
      manager);
  TpChannelManagerForeachChannelFunc method = iface->foreach_channel;

  if (method != NULL)
    {
      method (manager, func, user_data);
    }

}
