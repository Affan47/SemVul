entry_idisctype_handler (xmlNodePtr node, gpointer entry_pdata)
{
    struct entry_pdata *pdata = entry_pdata;
    GncAmountType type;
    char *str;
    gboolean ret;

    str = dom_tree_to_text (node);
    g_return_val_if_fail (str, FALSE);

    ret = gncAmountStringToType (str, &type);
    g_free (str);

    if (ret)
        gncEntrySetInvDiscountType(pdata->entry, type);

    return ret;
}
