dict_proc_param(const ref * pdict, const char *kstr, ref * pproc,
                bool defaultval)
{
    ref *pdval;

    if (pdict == 0 || dict_find_string(pdict, kstr, &pdval) <= 0) {
        if (defaultval)
            make_empty_const_array(pproc, a_readonly + a_executable);
        else
            make_t(pproc, t__invalid);
        return 1;
    }
    check_proc(*pdval);
    *pproc = *pdval;
    return 0;
}
