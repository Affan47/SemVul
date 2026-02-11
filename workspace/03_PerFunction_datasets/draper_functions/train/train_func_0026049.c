pack_known_header(Octstr *packed, long fieldnum, Octstr *value)
{
    List *elements = NULL;
    long startpos;
    long i;

    octstr_strip_blanks(value);

    startpos = octstr_len(packed);

    for (i = 0; i < TABLE_SIZE(headerinfo); i++) {
        if (headerinfo[i].header == fieldnum)
            break;
    }

    if (i == TABLE_SIZE(headerinfo)) {
        error(0, "WSP: Do not know how to encode header type %ld",
              fieldnum);
        goto error;
    }

    if (headerinfo[i].allows_list == LIST)
        elements = http_header_split_value(value);
    else if (headerinfo[i].allows_list == BROKEN_LIST)
        elements = http_header_split_auth_value(value);
    else
        elements = NULL;

    if (elements != NULL) {
        if (wsp_pack_list(packed, fieldnum, elements, i) < 0)
            goto error;
    } else {
        wsp_pack_short_integer(packed, fieldnum);
        if (headerinfo[i].func(packed, value) < 0)
            goto error;
    }

    gwlist_destroy(elements, octstr_destroy_item);
    return 0;

error:

    octstr_delete(packed, startpos, octstr_len(packed) - startpos);
    gwlist_destroy(elements, octstr_destroy_item);
    return -1;
}
