cx_list_destroy(cx_list *list, cx_free_func deallocate)
{
    cx_list_iterator l;


    if (!list)
        return;

    cx_assert(deallocate != NULL);

    l = _cx_list_begin(list);
    while (l != _cx_list_end(list)) {
        cx_lnode *node = l;

        l = _cx_list_next(list, l);
        _cx_lnode_destroy(_cx_list_extract(node), deallocate);
    }

    cx_assert(cx_list_empty(list));
    cx_free(list);

    return;

}
