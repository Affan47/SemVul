gcut_list_equal (const GList *list1, const GList *list2, GEqualFunc equal_func)
{
    const GList *node1, *node2;

    for (node1 = list1, node2 = list2;
         node1 && node2;
         node1 = g_list_next(node1), node2 = g_list_next(node2)) {
        if (!equal_func(node1->data, node2->data))
            return FALSE;
    }

    return node1 == NULL && node2 == NULL;
}
