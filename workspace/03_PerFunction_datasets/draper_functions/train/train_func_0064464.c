parse_xkb_xml_languagelist_node (IBusXKBConfigRegistryPrivate *priv,
                                 XMLNode *parent_node,
                                 const gchar *layout_name)
{
    XMLNode *node = parent_node;
    XMLNode *sub_node;
    GList *p;
    GList *lang_list = NULL;

    g_assert (node != NULL);
    g_assert (layout_name != NULL);
    for (p = node->sub_nodes; p; p = p->next) {
        sub_node = (XMLNode *) p->data;
        if (g_strcmp0 (sub_node->name, "iso639Id") == 0) {
            lang_list = g_list_append (lang_list,
                                       (gpointer) g_strdup (sub_node->text));
            continue;
        }
    }
    if (lang_list == NULL) {

        return;
    }
    if (g_hash_table_lookup (priv->layout_lang, layout_name) != NULL) {
        g_warning ("duplicated name %s exists", layout_name);
        return;
    }
    g_hash_table_insert (priv->layout_lang,
                         (gpointer) g_strdup (layout_name),
                         (gpointer) lang_list);
}
