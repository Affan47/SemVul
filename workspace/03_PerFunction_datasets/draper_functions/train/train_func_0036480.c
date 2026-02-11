xaccQueryAddDateMatchTS (QofQuery * q,
                         gboolean use_start, Timespec sts,
                         gboolean use_end, Timespec ets,
                         QofQueryOp op)
{
    QofQuery *tmp_q = NULL;
    QofQueryPredData *pred_data;
    GSList *param_list;

    if (!q || (!use_start && !use_end))
        return;

    tmp_q = qof_query_create ();

    if (use_start)
    {
        pred_data = qof_query_date_predicate (QOF_COMPARE_GTE, QOF_DATE_MATCH_NORMAL, sts);
        if (!pred_data)
        {
            qof_query_destroy (tmp_q);
            return;
        }

        param_list = qof_query_build_param_list (SPLIT_TRANS, TRANS_DATE_POSTED, NULL);
        qof_query_add_term (tmp_q, param_list, pred_data, QOF_QUERY_AND);
    }

    if (use_end)
    {
        pred_data = qof_query_date_predicate (QOF_COMPARE_LTE, QOF_DATE_MATCH_NORMAL, ets);
        if (!pred_data)
        {
            qof_query_destroy (tmp_q);
            return;
        }

        param_list = qof_query_build_param_list (SPLIT_TRANS, TRANS_DATE_POSTED, NULL);
        qof_query_add_term (tmp_q, param_list, pred_data, QOF_QUERY_AND);
    }

    qof_query_merge_in_place (q, tmp_q, op);
    qof_query_destroy (tmp_q);
}
