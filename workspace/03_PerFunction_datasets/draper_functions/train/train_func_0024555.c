inf_communication_central_method_send_all(InfCommunicationMethod* method,
                                          xmlNodePtr xml)
{
  InfCommunicationCentralMethodPrivate* priv;
  InfCommunicationRegistry* registry;
  InfCommunicationGroup* group;
  GSList* connections;
  GSList* item;
  InfXmlConnection* connection;
  gboolean is_registered;

  priv = INF_COMMUNICATION_CENTRAL_METHOD_PRIVATE(method);


  g_object_ref(method);
  registry = g_object_ref(priv->registry);
  group = g_object_ref(priv->group);

  connections = g_slist_copy(priv->connections);
  for(item = connections; item != NULL; item = item->next)
    g_object_ref(item->data);

  while(connections)
  {
    connection = INF_XML_CONNECTION(connections->data);


    is_registered = inf_communication_registry_is_registered(
      registry,
      group,
      connection
    );

    if(is_registered)
    {
      if(connections->next != NULL)
      {


        inf_communication_registry_send(
          registry,
          group,
          connection,
          xmlCopyNode(xml, 1)
        );
      }
      else
      {


        inf_communication_registry_send(registry, group, connection, xml);
        xml = NULL;
      }
    }

    g_object_unref(connection);
    connections = g_slist_delete_link(connections, connections);
  }

  g_object_unref(method);
  g_object_unref(registry);
  g_object_unref(group);

  if(xml != NULL)
    xmlFreeNode(xml);
}
