string_free_pdata (QofQueryPredData *pd)
{
    query_string_t pdata = (query_string_t) pd;

    VERIFY_PDATA (query_string_type);

    if (pdata->is_regex)
        regfree (&pdata->compiled);

    g_free (pdata->matchstring);
    g_free (pdata);
}
