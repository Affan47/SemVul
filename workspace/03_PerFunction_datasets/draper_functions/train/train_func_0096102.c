inf_communication_registry_entry_free(gpointer data)
{
  InfCommunicationRegistryEntry* entry;
  InfXmlConnectionStatus status;

  entry = (InfCommunicationRegistryEntry*)data;


  g_object_get(G_OBJECT(entry->key.connection), "status", &status, NULL);
  if(status != INF_XML_CONNECTION_CLOSING &&
     status != INF_XML_CONNECTION_CLOSED)
  {
    if(entry->queue_begin != NULL)
      inf_communication_registry_send_real(entry, G_MAXUINT);
  }

  if(entry->group)
  {
    g_object_weak_unref(
      G_OBJECT(entry->group),
      inf_communication_registry_group_unrefed,
      entry
    );
  }

  if(!entry->registered)
    g_object_unref(entry->key.connection);

  g_free(entry->key.publisher_id);
  g_slice_free(InfCommunicationRegistryEntry, entry);
}
