fl_string_decode(value_t *args, u_int32_t nargs)
{
    int term=0;
    if (nargs == 2) {
        term = (args[1] != FL_F);
    }
    else {
        argcount("string.decode", nargs, 1);
    }
    if (!fl_isstring(args[0]))
        type_error("string.decode", "string", args[0]);
    cvalue_t *cv = (cvalue_t*)ptr(args[0]);
    char *ptr = (char*)cv_data(cv);
    size_t nb = cv_len(cv);
    size_t nc = u8_charnum(ptr, nb);
    size_t newsz = nc*sizeof(uint32_t);
    if (term) newsz += sizeof(uint32_t);
    value_t wcstr = cvalue(wcstringtype, newsz);
    ptr = cv_data((cvalue_t*)ptr(args[0]));
    uint32_t *pwc = cvalue_data(wcstr);
    u8_toucs(pwc, nc, ptr, nb);
    if (term) pwc[nc] = 0;
    return wcstr;
}
