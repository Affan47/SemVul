qof_query_sort_equal (const QofQuerySort* qs1, const QofQuerySort* qs2)
{
    if (qs1 == qs2) return TRUE;
    if (!qs1 || !qs2) return FALSE;


    if (!qs1->param_list && !qs2->param_list) return TRUE;

    if (qs1->options != qs2->options) return FALSE;
    if (qs1->increasing != qs2->increasing) return FALSE;
    return (param_list_cmp (qs1->param_list, qs2->param_list) == 0);
}
