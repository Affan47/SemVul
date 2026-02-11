fl_numbertostring(value_t *args, u_int32_t nargs)
{
    if (nargs < 1 || nargs > 2)
        argcount("number->string", nargs, 2);
    value_t n = args[0];
    int neg = 0;
    uint64_t num;
    if (isfixnum(n))      num = numval(n);
    else if (!iscprim(n)) type_error("number->string", "integer", n);
    else num = conv_to_uint64(cp_data((cprim_t*)ptr(n)),
                              cp_numtype((cprim_t*)ptr(n)));
    if (numval(fl_compare(args[0],fixnum(0))) < 0) {
        num = -num;
        neg = 1;
    }
    unsigned long radix = 10;
    if (nargs == 2)
        radix = get_radix_arg(args[1], "number->string");
    char buf[128];
    char *str = uint2str(buf, sizeof(buf), num, radix);
    if (neg && str > &buf[0])
        *(--str) = '-';
    return string_from_cstr(str);
}
