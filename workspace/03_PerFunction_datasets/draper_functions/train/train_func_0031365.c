p_is_positive(li_object *args) {
    assert_nargs(1, args);
    assert_number(li_car(args));
    return li_boolean(li_to_number(li_car(args)) >= 0);
}
