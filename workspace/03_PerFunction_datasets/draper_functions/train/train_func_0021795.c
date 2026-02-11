lookup_namespaced_node(xmlNodePtr node, gpointer opaque)
{
    struct LookupNamespacedNodeData* data = opaque;

    if (node->ns == NULL)
        return TRUE;

    if (g_strcmp0((char *)node->ns->href, data->ns_uri) == 0) {
        data->node = node;
        return FALSE;
    }

    return TRUE;
}
