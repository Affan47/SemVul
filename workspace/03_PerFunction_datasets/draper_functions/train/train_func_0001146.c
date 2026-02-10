qof_query_core_predicate_free (QofQueryPredData *pdata)
{
    QueryPredDataFree free_fcn;

    g_return_if_fail (pdata);
    g_return_if_fail (pdata->type_name);

    free_fcn = qof_query_predicate_free (pdata->type_name);
    free_fcn (pdata);
}
