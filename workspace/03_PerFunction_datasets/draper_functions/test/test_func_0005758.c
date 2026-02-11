merge_books (GList *l1, GList *l2)
{
    GList *res = NULL;
    GList *node;

    res = g_list_copy (l1);

    for (node = l2; node; node = node->next)
    {
        if (g_list_index (res, node->data) == -1)
            res = g_list_prepend (res, node->data);
    }

    return res;
}
