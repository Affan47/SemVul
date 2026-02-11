p_read(li_object *args) {
    FILE *f;

    f = stdin;
    if (args) {
        assert_nargs(1, args);
        assert_port(li_car(args));
        f = li_to_port(li_car(args)).file;
    }
    return li_read(f);
}
