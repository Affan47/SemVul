p_string_length(li_object *args) {
    assert_nargs(1, args);
    assert_string(li_car(args));
    return li_number(strlen(li_to_string(li_car(args))));
}
