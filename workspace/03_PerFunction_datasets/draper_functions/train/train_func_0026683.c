hybrid_pref_get_boolean(HybridPref *pref, const gchar *name)
{
    xmlnode *node;
    gchar   *type;
    gchar   *value;

    pref = pref ? pref : hybrid_pref;
    g_return_val_if_fail(pref->root != NULL, FALSE);

    if (!(node = xmlnode_find(pref->root, name))) {
        return FALSE;
    }

    if (!xmlnode_has_prop(node, "type")) {
        hybrid_debug_info("pref", "invalid pref node.");
        return FALSE;
    }

    type = xmlnode_prop(node, "type");

    if (g_strcmp0(type, "bool") != 0) {
        hybrid_debug_error("pref",
                           "bool pref node with a type which is not bool.");
        return FALSE;
    }

    value = xmlnode_content(node);

    if (g_strcmp0(value, "0") == 0) {
        g_free(value);
        return FALSE;
    } else {
        g_free(value);
        return TRUE;
    }
}
