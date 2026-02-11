dict_float_array_check_param(const gs_memory_t *mem,
                             const ref * pdict, const char *kstr,
                             uint len, float *fvec, const float *defaultvec,
                             int under_error, int over_error)
{
    ref *pdval;
    uint size;
    int code;

    if (pdict == 0 || dict_find_string(pdict, kstr, &pdval) <= 0) {
        if (defaultvec == NULL)
            return 0;
        memcpy(fvec, defaultvec, len * sizeof(float));
        return len;
    }

    if (!r_is_array(pdval))
        return_error(e_typecheck);
    size = r_size(pdval);
    if (over_error < 0 && size > len)
        return_error(over_error);

    size = min(size, len);
    code = process_float_array(mem, pdval, size, fvec);
    return (code < 0 ? code :
            size == len || under_error >= 0 ? size :
            gs_note_error(under_error));
}
