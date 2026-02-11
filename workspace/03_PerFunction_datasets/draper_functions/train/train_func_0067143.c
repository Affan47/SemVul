inf_communication_factory_supports_method(InfCommunicationFactory* factory,
                                          const gchar* network,
                                          const gchar* method_name)
{
  InfCommunicationFactoryIface* iface;

  g_return_val_if_fail(INF_COMMUNICATION_IS_FACTORY(factory), FALSE);
  g_return_val_if_fail(network != NULL, FALSE);
  g_return_val_if_fail(method_name != NULL, FALSE);

  iface = INF_COMMUNICATION_FACTORY_GET_IFACE(factory);
  g_return_val_if_fail(iface->supports_method != NULL, FALSE);

  return iface->supports_method(factory, network, method_name);
}
