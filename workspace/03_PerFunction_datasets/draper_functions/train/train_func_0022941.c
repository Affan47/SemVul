make_tree(void)
{
    GNode *tree;
    tree_item *item;
    gchar **array;
    gchar **array_ptr;

    if (G_TRYLOCK(tree) == FALSE)
        return NULL;

    cancel = FALSE;
    if (last_tree_ok())
        return last_tree;

    invalidate_last_tree();

    array_ptr = array = get_sorted_files_array();
    if (array == NULL) {
        G_UNLOCK(tree);
        return NULL;
    }

    item = new_item(g_strdup(""), g_strdup(""));
    tree = g_node_new(item);


    while (*array_ptr != NULL)
        make_tree_rec(tree, &array_ptr);

    g_free(array);

    compress_tree(tree);

    g_node_traverse(tree, G_POST_ORDER, G_TRAVERSE_ALL, -1,
                    (GNodeTraverseFunc) to_utf8, NULL);

    print_tree(tree, 0);

    last_tree = tree;
    touch(&timestamp);
    return tree;
}
