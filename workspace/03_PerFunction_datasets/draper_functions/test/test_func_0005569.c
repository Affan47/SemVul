infd_directory_add_subreq_add_node(InfdDirectory* directory,
                                   InfXmlConnection* connection,
                                   guint node_id,
                                   InfdDirectoryNode* parent,
                                   InfCommunicationHostedGroup* group,
                                   const InfdNotePlugin* plugin,
                                   const gchar* name,
                                   GError** error)
{
  InfdDirectorySubreq* request;
  InfdSessionProxy* proxy;

  proxy = infd_directory_create_session_proxy_for_storage(
    directory,
    parent,
    group,
    name,
    plugin,
    INF_SESSION_RUNNING,
    NULL,
    NULL,
    error
  );

  if(proxy == NULL)
    return NULL;

  request = infd_directory_add_subreq_common(
    directory,
    INFD_DIRECTORY_SUBREQ_ADD_NODE,
    connection,
    node_id
  );

  request->shared.add_node.parent = parent;
  request->shared.add_node.group = group;
  request->shared.add_node.plugin = plugin;
  request->shared.add_node.name = g_strdup(name);
  request->shared.add_node.proxy = proxy;

  g_object_ref(group);
  return request;
}
