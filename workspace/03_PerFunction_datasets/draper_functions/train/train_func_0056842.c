spl_lot_handler(xmlNodePtr node, gpointer data)
{
    struct split_pdata *pdata = data;
    GncGUID *id = dom_tree_to_guid(node);
    GNCLot *lot;

    g_return_val_if_fail(id, FALSE);

    lot = gnc_lot_lookup (id, pdata->book);
    if (!lot && gnc_transaction_xml_v2_testing &&
            !guid_equal (id, guid_null ()))
    {
        lot = gnc_lot_new (pdata->book);
        gnc_lot_set_guid (lot, *id);
    }

    gnc_lot_add_split (lot, pdata->split);

    g_free(id);

    return TRUE;
}
