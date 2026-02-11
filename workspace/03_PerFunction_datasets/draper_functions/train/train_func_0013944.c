gvir_config_xml_foreach_child(xmlNodePtr node,
                                   GVirConfigXmlNodeIterator iter_func,
                                   gpointer opaque)
{
    xmlNodePtr it;

    g_return_if_fail(iter_func != NULL);

    it = node->children;
    while (it != NULL) {
        gboolean cont;
        xmlNodePtr next = it->next;

        if (!xmlIsBlankNode(it)) {
            cont = iter_func(it, opaque);
            if (!cont)
                break;
        }

        it = next;
    }
}
