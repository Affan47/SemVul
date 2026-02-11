p_system(li_object *args) {
    int ret;

    assert_nargs(1, args);
    assert_string(li_car(args));
    if ((ret = system(li_to_string(li_car(args)))))
        return li_number(ret);
    return li_null;
}
