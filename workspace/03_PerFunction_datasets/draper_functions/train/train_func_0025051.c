data_to_utf8str(utf8str_t *u, krb5_data d)
{
    u->utf8str_t_len = d.length;
    if (d.data) {
        u->utf8str_t_val = malloc(d.length);
        if (u->utf8str_t_val == NULL)
            return -1;
        memcpy(u->utf8str_t_val, d.data, d.length);
    } else
        u->utf8str_t_val = NULL;
    return 0;
}
