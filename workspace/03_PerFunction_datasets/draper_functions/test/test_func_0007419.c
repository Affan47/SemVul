p_list_tail(li_object *args) {
    li_object *lst;
    int k;

    assert_nargs(2, args);
    assert_integer(li_cadr(args));
    lst = li_car(args);
    for (k = li_to_integer(li_cadr(args)); k; k--) {
        if (lst && !li_is_pair(lst))
            li_error("not a list", li_car(args));
        lst = li_cdr(lst);
    }
    return lst;
}
