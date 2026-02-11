infc_browser_add_subreq_add_node(InfcBrowser* browser,
                                 guint node_id,
                                 InfcBrowserNode* parent,
                                 const InfcNotePlugin* plugin,
                                 const gchar* name,
                                 InfcNodeRequest* request,
                                 InfCommunicationJoinedGroup* group)
{
  InfcBrowserSubreq* subreq;

  subreq = infc_browser_add_subreq_common(
    browser,
    INFC_BROWSER_SUBREQ_ADD_NODE,
    node_id
  );

  subreq->shared.add_node.parent = parent;
  subreq->shared.add_node.plugin = plugin;
  subreq->shared.add_node.name = g_strdup(name);
  subreq->shared.add_node.request = request;
  subreq->shared.add_node.subscription_group = group;

  if(request != NULL)
    g_object_ref(request);
  g_object_ref(group);

  return subreq;
}
