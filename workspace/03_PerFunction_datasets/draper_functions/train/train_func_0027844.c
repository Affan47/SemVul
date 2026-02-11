month_arg(VALUE arg)
{
    int i, mon;

    VALUE s = rb_check_string_type(arg);
    if (!NIL_P(s)) {
        mon = 0;
        for (i=0; i<12; i++) {
            if (RSTRING_LEN(s) == 3 &&
                STRCASECMP(months[i], RSTRING_PTR(s)) == 0) {
                mon = i+1;
                break;
            }
        }
        if (mon == 0) {
            char c = RSTRING_PTR(s)[0];

            if ('0' <= c && c <= '9') {
                mon = obj2int(s);
            }
        }
    }
    else {
        mon = obj2int(arg);
    }
    return mon;
}
