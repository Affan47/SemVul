reparent_children (GUPnPMediaCollection *collection)
{
        GList *it;
        xmlNode *container_node;

        container_node = gupnp_didl_lite_object_get_xml_node
                                        (collection->priv->container);


        it = g_list_last (collection->priv->items);
        while (it) {
                xmlNode *node;

                node = gupnp_didl_lite_object_get_xml_node
                                        (GUPNP_DIDL_LITE_OBJECT (it->data));
                xmlUnlinkNode (node);
                node = xmlAddChild (container_node, node);

                it = it->prev;
        }
}
