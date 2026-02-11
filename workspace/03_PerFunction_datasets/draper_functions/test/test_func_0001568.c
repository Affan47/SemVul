p_atan(li_object *args) {
    assert_number(li_car(args));
    if (li_cdr(args)) {
        assert_nargs(2, args);
        assert_number(li_cadr(args));
        return li_number(atan2(li_to_number(li_cadr(args)), li_to_number(li_car(args))));
    }
    return li_number(atan(li_to_number(li_car(args))));
}
