commodity_ref_to_dom_tree(const char *tag, const gnc_commodity *c)
{
    xmlNodePtr ret;
    gchar *namespace, *mnemonic;

    g_return_val_if_fail(c, NULL);

    ret = xmlNewNode(NULL, BAD_CAST tag);

    if (!gnc_commodity_get_namespace(c) || !gnc_commodity_get_mnemonic(c))
    {
        return NULL;
    }
    namespace = g_strdup (gnc_commodity_get_namespace_compat(c));
    mnemonic = g_strdup (gnc_commodity_get_mnemonic(c));
    xmlNewTextChild(ret, NULL, BAD_CAST "cmdty:space",
		    checked_char_cast (namespace));
    xmlNewTextChild(ret, NULL, BAD_CAST "cmdty:id",
		    checked_char_cast (mnemonic));
    g_free (namespace);
    g_free (mnemonic);
    return ret;
}
