dict_uint_param(const ref * pdict, const char *kstr,
                uint minval, uint maxval, uint defaultval, uint * pvalue)
{
    ref *pdval;
    int code;
    uint ival;

    if (pdict == 0 || dict_find_string(pdict, kstr, &pdval) <= 0) {
        ival = defaultval;
        code = 1;
    } else {
        check_type_only(*pdval, t_integer);
        if (pdval->value.intval != (uint) pdval->value.intval)
            return_error(e_rangecheck);
        ival = (uint) pdval->value.intval;
        code = 0;
    }
    if (ival < minval || ival > maxval) {
        if (code == 1)
            return_error(e_undefined);
        else
            return_error(e_rangecheck);
    }
    *pvalue = ival;
    return code;
}
