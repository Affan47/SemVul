p_assv(li_object *args) {
    li_object *lst;

    assert_nargs(2, args);
    for (lst = li_cadr(args); lst; lst = li_cdr(lst)) {
        if (!li_is_pair(lst))
            li_error("not a list", li_cadr(args));
        if (li_is_eqv(li_car(args), li_caar(lst)))
            return li_car(lst);
    }
    return li_false;
}
