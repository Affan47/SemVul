_cx_list_sort(cx_list *list, cx_compare_func compare)
{

    if (_cx_list_size(list) > 1 && !_cx_list_sorted(list, compare)) {
        cx_list tmp;
        cx_lnode *node;
        cxsize middle = _cx_list_size(list) / 2;


        _cx_list_init(&tmp);
        node = _cx_list_begin(list);

        while (middle--)
            node = _cx_list_next(list, node);

        _cx_list_transfer(_cx_list_begin(&tmp), node, _cx_list_end(list));
        _cx_list_sort(list, compare);
        _cx_list_sort(&tmp, compare);

        _cx_list_merge(list, &tmp, compare);
    }

    return;

}
