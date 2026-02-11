p_for_each(li_object *args) {
    li_object *proc;

    assert_nargs(2, args);
    assert_procedure(li_car(args));
    proc = li_car(args);
    args = li_cadr(args);
    while (args) {
        li_apply(proc, li_cons(li_car(args), li_null));
        args = li_cdr(args);
    }
    return li_null;
}
