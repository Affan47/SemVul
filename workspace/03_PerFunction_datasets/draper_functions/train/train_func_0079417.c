FAPI_FF_get_charstring(gs_fapi_font *ff, int index, byte *buf,
                       ushort buf_length)
{
    ref *pdr = pfont_dict(((gs_font_base *) ff->client_font_data2));
    ref *CharStrings, eltp[2];

    if (dict_find_string(pdr, "CharStrings", &CharStrings) <= 0)
        return 0;
    if (dict_index_entry(CharStrings, index, eltp) < 0)
        return 0;
    if (buf && buf_length && buf_length >= r_size(&eltp[1])) {
        memcpy(buf, eltp[1].value.const_bytes, r_size(&eltp[1]));
    }
    return (r_size(&eltp[1]));
}
