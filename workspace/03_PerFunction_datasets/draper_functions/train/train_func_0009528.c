krb5_dbe_set_string(krb5_context context, krb5_db_entry *entry,
                    const char *key, const char *value)
{
    krb5_error_code code;
    const char *pos, *end, *mapkey, *mapval;
    struct k5buf buf;
    krb5_boolean found = FALSE;
    krb5_tl_data tl_data;
    ssize_t len;


    code = begin_attrs(context, entry, &pos, &end);
    if (code)
        return code;
    k5_buf_init_dynamic(&buf);
    while (next_attr(&pos, end, &mapkey, &mapval)) {
        if (strcmp(mapkey, key) == 0) {
            if (value != NULL) {
                k5_buf_add_len(&buf, mapkey, strlen(mapkey) + 1);
                k5_buf_add_len(&buf, value, strlen(value) + 1);
            }
            found = TRUE;
        } else {
            k5_buf_add_len(&buf, mapkey, strlen(mapkey) + 1);
            k5_buf_add_len(&buf, mapval, strlen(mapval) + 1);
        }
    }


    if (!found && value != NULL) {
        k5_buf_add_len(&buf, key, strlen(key) + 1);
        k5_buf_add_len(&buf, value, strlen(value) + 1);
    }

    len = k5_buf_len(&buf);
    if (len == -1)
        return ENOMEM;
    if (len > 65535)
        return KRB5_KDB_STRINGS_TOOLONG;
    tl_data.tl_data_type = KRB5_TL_STRING_ATTRS;
    tl_data.tl_data_contents = (krb5_octet *)k5_buf_data(&buf);
    tl_data.tl_data_length = len;

    code = krb5_dbe_update_tl_data(context, entry, &tl_data);
    k5_free_buf(&buf);
    return code;
}
