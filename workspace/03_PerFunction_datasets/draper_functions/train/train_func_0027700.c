build_stlg_tree(Module_table *module_head, List *list)
{
    Module_table **m_array;
    int n_modules;
    int i;

    m_array = get_sorted_module_array(module_head, &n_modules);

    for (i = n_modules - 1; i > -1; i--) {
        List *sublist = get_stlgs_in_module(list, m_array[i]);

        list = list_remove_sub_part(list, sublist);

#ifdef DEBUG_BUILD_TREE
        fprintf(stderr, ">>> SuperTlg in %s <<<\n", m_array[i]->name);
        put_stlgs_short(stderr, sublist);
#endif

        sublist = coalescing(sublist);

#ifdef DEBUG_BUILD_TREE
        fprintf(stderr, ">>> coalescing <<<\n");
        put_stlgs(stderr, sublist);
#endif

        sublist = expanding(sublist);

#ifdef DEBUG_BUILD_TREE
        fprintf(stderr, ">>> expanding <<<\n");
        put_stlgs_short(stderr, sublist);
#endif

        list = list_concat(list, sublist);
        list = sort_stlgs(list);
    }

    return list;
}
