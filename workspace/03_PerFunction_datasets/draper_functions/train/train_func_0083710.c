qof_query_guid_predicate (QofGuidMatch options, GList *guid_list)
{
    query_guid_t pdata;
    GList *node;


    if (!guid_list)
        g_return_val_if_fail (options == QOF_GUID_MATCH_NULL, NULL);

    pdata = g_new0 (query_guid_def, 1);
    pdata->pd.how = QOF_COMPARE_EQUAL;
    pdata->pd.type_name = query_guid_type;
    pdata->options = options;

    pdata->guids = g_list_copy (guid_list);
    for (node = pdata->guids; node; node = node->next)
    {
        GncGUID *guid = guid_malloc ();
        *guid = *((GncGUID *)node->data);
        node->data = guid;
    }
    return ((QofQueryPredData*)pdata);
}
