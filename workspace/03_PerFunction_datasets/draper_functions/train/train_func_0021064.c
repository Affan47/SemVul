qof_query_equal (const QofQuery *q1, const QofQuery *q2)
{
    GList *or1, *or2;

    if (q1 == q2) return TRUE;
    if (!q1 || !q2) return FALSE;

    if (g_list_length (q1->terms) != g_list_length (q2->terms)) return FALSE;
    if (q1->max_results != q2->max_results) return FALSE;

    for (or1 = q1->terms, or2 = q2->terms; or1;
            or1 = or1->next, or2 = or2->next)
    {
        GList *and1, *and2;

        and1 = or1->data;
        and2 = or2->data;

        if (g_list_length (and1) != g_list_length (and2)) return FALSE;

        for ( ; and1; and1 = and1->next, and2 = and2->next)
            if (!qof_query_term_equal (and1->data, and2->data))
                return FALSE;
    }

    if (!qof_query_sort_equal (&(q1->primary_sort), &(q2->primary_sort)))
        return FALSE;
    if (!qof_query_sort_equal (&(q1->secondary_sort), &(q2->secondary_sort)))
        return FALSE;
    if (!qof_query_sort_equal (&(q1->tertiary_sort), &(q2->tertiary_sort)))
        return FALSE;

    return TRUE;
}
