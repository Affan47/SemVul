hybrid_pref_set_string(HybridPref *pref, const gchar *name, const gchar *value)
{
    xmlnode *node;

    pref = pref ? pref : hybrid_pref;
    g_return_if_fail(pref->root != NULL);

    if (!(node = xmlnode_find(pref->root, name))) {
        node = xmlnode_new_child(pref->root, name);
    }

    if (xmlnode_has_prop(node, "type")) {
        xmlnode_set_prop(node, "type", "string");
    } else {
        xmlnode_new_prop(node, "type", "string");
    }

    xmlnode_set_content(node, value);
}
