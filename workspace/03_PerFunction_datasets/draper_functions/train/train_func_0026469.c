infc_browser_sync_in_synchronization_failed_cb(InfSession* session,
                                               InfXmlConnection* connection,
                                               GError* error,
                                               gpointer user_data)
{
  InfcBrowserSyncIn* sync_in;
  sync_in = (InfcBrowserSyncIn*)user_data;


  if(connection != sync_in->connection) return;

  infc_browser_node_remove(sync_in->browser, sync_in->node, NULL);
  infc_browser_remove_sync_in(sync_in->browser, sync_in);
}
