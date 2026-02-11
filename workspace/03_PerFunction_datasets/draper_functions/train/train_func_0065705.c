_cx_slist_sort(cx_slist *list, cx_compare_func compare)
{

    if (_cx_slist_size(list) > 1) {
        cx_slist tmp;
        cx_slnode *node;
        cxsize middle = _cx_slist_size(list) / 2;


        _cx_slist_init(&tmp);

        node = list->head.next;
        while (--middle)
            node = node->next;

        _cx_slist_splice_after(&tmp.head, &list->head, node);
        _cx_slist_sort(list, compare);
        _cx_slist_sort(&tmp, compare);

        _cx_slist_merge(list, &tmp, compare);
    }

    return;

}
