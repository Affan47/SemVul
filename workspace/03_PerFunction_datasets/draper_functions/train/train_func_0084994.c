qof_query_num_terms (QofQuery *q)
{
    GList *o;
    int n = 0;
    if (!q) return 0;
    for (o = q->terms; o; o = o->next)
        n += g_list_length(o->data);
    return n;
}
