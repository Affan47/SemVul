p_quotient(li_object *args) {
    assert_nargs(2, args);
    assert_integer(li_car(args));
    assert_integer(li_cadr(args));
    if (!li_to_integer(li_cadr(args)))
        li_error("arg2 must be non-zero", args);
    return li_number(li_to_integer(li_car(args)) / li_to_integer(li_cadr(args)));
}
