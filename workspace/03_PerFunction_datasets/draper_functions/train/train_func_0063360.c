p_list_to_vector(li_object *args) {
    assert_nargs(1, args);
    assert_list(li_car(args));
    return li_vector(li_car(args));
}
