qof_query_has_term_type (QofQuery *q, QofQueryParamList *term_param)
{
    GList *or;
    GList *and;

    if (!q || !term_param)
        return FALSE;

    for (or = q->terms; or; or = or->next)
    {
        for (and = or->data; and; and = and->next)
        {
            QofQueryTerm *qt = and->data;
            if (!param_list_cmp (term_param, qt->param_list))
                return TRUE;
        }
    }

    return FALSE;
}
