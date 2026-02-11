parse_xkb_xml_top_node (IBusXKBConfigRegistryPrivate *priv,
                        XMLNode *parent_node)
{
    XMLNode *node = parent_node;
    XMLNode *sub_node;
    GList *p;

    g_assert (priv != NULL);
    g_assert (node != NULL);

    if (g_strcmp0 (node->name, "xkbConfigRegistry") != 0) {
        g_warning ("node has no xkbConfigRegistry name");
        return;
    }
    for (p = node->sub_nodes; p; p = p->next) {
        sub_node = (XMLNode *) p->data;
        if (g_strcmp0 (sub_node->name, "layoutList") == 0) {
            break;
        }
    }
    if (p == NULL) {
        g_warning ("xkbConfigRegistry node has no layoutList node");
        return;
    }
    node = sub_node;
    for (p = node->sub_nodes; p; p = p->next) {
        sub_node = (XMLNode *) p->data;
        if (g_strcmp0 (sub_node->name, "layout") == 0) {
            parse_xkb_xml_layout_node (priv, sub_node);
            continue;
        }
    }
}
