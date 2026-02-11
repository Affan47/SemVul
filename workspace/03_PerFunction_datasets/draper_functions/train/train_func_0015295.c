pack_content_range(Octstr *packed, Octstr *value)
{
    Octstr *bytes;
    long pos;
    long firstbyte, lastbyte, instancelen;
    Octstr *encoding;

    bytes = octstr_imm("bytes ");
    if (octstr_ncompare(value, bytes, octstr_len(bytes)) != 0)
        goto error;

    pos = octstr_len(bytes);
    while (isspace(octstr_get_char(value, pos)))
        pos++;
    if (octstr_get_char(value, pos) == '*')
        goto warning;
    pos = octstr_parse_long(&firstbyte, value, pos, 10);
    if (pos < 0)
        goto error;

    while (isspace(octstr_get_char(value, pos)))
        pos++;
    if (octstr_get_char(value, pos++) != '-')
        goto error;

    pos = octstr_parse_long(&lastbyte, value, pos, 10);
    if (pos < 0)
        goto error;

    while (isspace(octstr_get_char(value, pos)))
        pos++;
    if (octstr_get_char(value, pos++) != '/')
        goto error;

    while (isspace(octstr_get_char(value, pos)))
        pos++;
    if (octstr_get_char(value, pos) == '*')
        goto warning;
    pos = octstr_parse_long(&instancelen, value, pos, 10);
    if (pos < 0)
        goto error;


    if (lastbyte < firstbyte || instancelen < lastbyte) {
        warning(0, "WSP: Content-Range '%s' is invalid.",
                octstr_get_cstr(value));
        return -1;
    }

    encoding = octstr_create("");
    octstr_append_uintvar(encoding, firstbyte);
    octstr_append_uintvar(encoding, instancelen);
    wsp_pack_value(packed, encoding);
    octstr_destroy(encoding);

    return 0;

error:
    warning(0, "WSP: Cannot parse Content-Range '%s'.",
            octstr_get_cstr(value));
    return -1;

warning:
    warning(0, "WSP: Cannot encode Content-Range '%s'.",
            octstr_get_cstr(value));
    return -1;
}
