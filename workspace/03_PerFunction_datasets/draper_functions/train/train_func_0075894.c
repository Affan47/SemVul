fl_string_reverse(value_t *args, u_int32_t nargs)
{
    argcount("string.reverse", nargs, 1);
    if (!fl_isstring(args[0]))
        type_error("string.reverse", "string", args[0]);
    size_t len = cv_len((cvalue_t*)ptr(args[0]));
    value_t ns = cvalue_string(len);
    u8_reverse(cvalue_data(ns), cvalue_data(args[0]), len);
    return ns;
}
