choice_free_pdata (QofQueryPredData *pd)
{
    query_choice_t pdata = (query_choice_t)pd;
    GList *node;
    VERIFY_PDATA (query_choice_type);
    for (node = pdata->guids; node; node = node->next)
    {
        guid_free (node->data);
    }
    g_list_free (pdata->guids);
    g_free (pdata);
}
