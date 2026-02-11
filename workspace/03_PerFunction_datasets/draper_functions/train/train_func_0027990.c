set_dlr_mask(List *headers, Octstr *dlr_url)
{
    Octstr *dlrmaskos;
    long dlr_mask;
    long masklen;

    if (dlr_url == NULL) {
        return 0;
    }

    dlrmaskos = http_header_value(headers, octstr_imm("X-Kannel-DLR-Mask"));
    if (dlrmaskos == NULL) {
        return 0;
    }

    if ((masklen = octstr_parse_long(&dlr_mask, dlrmaskos, 0, 10)) != -1 &&
             masklen == octstr_len(dlrmaskos) &&
             dlr_mask >= -1 && dlr_mask <= 31) {
         octstr_destroy(dlrmaskos);
         return dlr_mask;
    }

    warning(0, "unparsable dlr mask, rejected");
    octstr_destroy(dlrmaskos);
    return 0;
}
