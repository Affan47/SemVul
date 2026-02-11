cid_font_system_info_param(gs_cid_system_info_t *pcidsi, const ref *prfont)
{
    ref *prcidsi;

    if (dict_find_string(prfont, "CIDSystemInfo", &prcidsi) <= 0)
        return_error(e_rangecheck);
    return cid_system_info_param(pcidsi, prcidsi);
}
