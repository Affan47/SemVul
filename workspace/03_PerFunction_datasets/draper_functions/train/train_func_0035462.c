inf_communication_registry_send(InfCommunicationRegistry* registry,
                                InfCommunicationGroup* group,
                                InfXmlConnection* connection,
                                xmlNodePtr xml)
{
  InfCommunicationRegistryPrivate* priv;
  InfCommunicationRegistryKey key;
  InfCommunicationRegistryEntry* entry;

  g_return_if_fail(INF_COMMUNICATION_IS_REGISTRY(registry));
  g_return_if_fail(INF_COMMUNICATION_IS_GROUP(group));
  g_return_if_fail(INF_IS_XML_CONNECTION(connection));
  g_return_if_fail(xml != NULL);

  priv = INF_COMMUNICATION_REGISTRY_PRIVATE(registry);
  key.connection = connection;
  key.publisher_id =
    inf_communication_group_get_publisher_id(group, connection);
  key.group_name = inf_communication_group_get_name(group);

  entry = g_hash_table_lookup(priv->entries, &key);
  g_assert(entry != NULL && entry->registered == TRUE);

  xmlUnlinkNode(xml);
  if(entry->queue_end == NULL)
  {
    entry->queue_begin = xml;
    entry->queue_end = xml;
  }
  else
  {
    entry->queue_end->next = xml;
    entry->queue_end = xml;
  }


  if(entry->inner_count == 0)
  {
    inf_communication_registry_send_real(
      entry,
      INF_COMMUNICATION_REGISTRY_INNER_QUEUE_LIMIT - entry->inner_count
    );
  }

  g_free(key.publisher_id);
}
