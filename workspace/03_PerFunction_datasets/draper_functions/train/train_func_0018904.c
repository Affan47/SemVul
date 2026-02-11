gupnp_didl_lite_object_new_from_xml (xmlNode     *xml_node,
                                     GUPnPXMLDoc *xml_doc,
                                     xmlNs       *upnp_ns,
                                     xmlNs       *dc_ns,
                                     xmlNs       *dlna_ns,
                                     xmlNs       *pv_ns)
{
        g_return_val_if_fail (xml_node != NULL, NULL);
        g_return_val_if_fail (xml_node->name != NULL, NULL);
        g_return_val_if_fail (upnp_ns != NULL, NULL);
        g_return_val_if_fail (dc_ns != NULL, NULL);
        g_return_val_if_fail (dlna_ns != NULL, NULL);

        if (g_ascii_strcasecmp ((char *) xml_node->name, "container") == 0)
                return g_object_new (GUPNP_TYPE_DIDL_LITE_CONTAINER,
                                     "xml-node", xml_node,
                                     "xml-doc", xml_doc,
                                     "upnp-namespace", upnp_ns,
                                     "dc-namespace", dc_ns,
                                     "dlna-namespace", dlna_ns,
                                     "pv-namespace", pv_ns,
                                     NULL);
        else if (g_ascii_strcasecmp ((char *) xml_node->name, "item") == 0)
                return g_object_new (GUPNP_TYPE_DIDL_LITE_ITEM,
                                     "xml-node", xml_node,
                                     "xml-doc", xml_doc,
                                     "upnp-namespace", upnp_ns,
                                     "dc-namespace", dc_ns,
                                     "dlna-namespace", dlna_ns,
                                     "pv-namespace", pv_ns,
                                     NULL);
        else
                return NULL;
}
