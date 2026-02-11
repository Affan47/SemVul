seahorse_util_string_slist_copy (GSList *list)
{
    GSList *l = NULL;
    for ( ; list; list = g_slist_next(list))
        l = g_slist_append (l, g_strdup(list->data));
    return l;
}
