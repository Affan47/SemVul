set_query_sort (QofQuery *q, sort_type_t sort_code)
{
    GSList *p1 = NULL, *p2 = NULL, *p3 = NULL, *standard;

    standard = g_slist_prepend (NULL, QUERY_DEFAULT_SORT);

    switch (sort_code)
    {
    case BY_STANDARD:
        p1 = standard;
        break;
    case BY_DATE:
        p1 = g_slist_prepend (p1, TRANS_DATE_POSTED);
        p1 = g_slist_prepend (p1, SPLIT_TRANS);
        p2 = standard;
        break;
    case BY_DATE_ENTERED:
        p1 = g_slist_prepend (p1, TRANS_DATE_ENTERED);
        p1 = g_slist_prepend (p1, SPLIT_TRANS);
        p2 = standard;
        break;
    case BY_DATE_RECONCILED:
        p1 = g_slist_prepend (p1, SPLIT_RECONCILE);
        p2 = g_slist_prepend (p2, SPLIT_DATE_RECONCILED);
        p3 = standard;
        break;
    case BY_NUM:
        p1 = g_slist_prepend (p1, TRANS_NUM);
        p1 = g_slist_prepend (p1, SPLIT_TRANS);
        p2 = standard;
        break;
    case BY_AMOUNT:
        p1 = g_slist_prepend (p1, SPLIT_VALUE);
        p2 = standard;
        break;
    case BY_MEMO:
        p1 = g_slist_prepend (p1, SPLIT_MEMO);
        p2 = standard;
        break;
    case BY_DESC:
        p1 = g_slist_prepend (p1, TRANS_DESCRIPTION);
        p1 = g_slist_prepend (p1, SPLIT_TRANS);
        p2 = standard;
        break;
    case BY_NONE:
        g_slist_free (standard);
        break;
    default:
        g_slist_free (standard);
        g_return_if_fail (FALSE);
        break;
    }

    qof_query_set_sort_order (q, p1, p2, p3);
}
