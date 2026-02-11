p_list_to_string(li_object *args) {
    li_object *lst, *str;
    int i, n;
    char *s;

    assert_nargs(1, args);
    assert_list(li_car(args));
    lst = li_car(args);
    n = li_length(lst);
    s = li_allocate(li_null, n + 1, sizeof(*s));
    for (i = 0; i < n; i++) {
        assert_character(li_car(lst));
        s[i] = li_to_character(li_car(lst));
        lst = li_cdr(lst);
    }
    s[i] = '\0';
    str = li_string(s);
    free(s);
    return str;
}
