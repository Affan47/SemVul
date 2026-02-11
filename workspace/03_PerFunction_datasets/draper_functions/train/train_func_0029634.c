acquire_cid_system_info(ref *psia, const ref *op)
{
    ref *prcidsi;

    if (dict_find_string(op, "CIDSystemInfo", &prcidsi) <= 0) {
        make_empty_array(psia, a_readonly);
        return 1;
    }
    if (r_has_type(prcidsi, t_dictionary)) {
        make_array(psia, a_readonly, 1, prcidsi);
        return 0;
    }
    if (!r_is_array(prcidsi))
        return_error(e_typecheck);
    *psia = *prcidsi;
    return 0;
}
