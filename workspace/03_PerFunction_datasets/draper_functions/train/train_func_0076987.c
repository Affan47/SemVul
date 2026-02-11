find_font_dict(i_ctx_t *i_ctx_p, ref *topdict, ref **fontdict, const char *key)
{
    int code;
    ref val;

    if (*fontdict)
        return 0;
    if (dict_find_string(topdict, key, fontdict) > 0)
        return 0;
    if ((code = dict_create(8,  &val)) < 0)
        return code;
    if ((code = idict_put_c_name(i_ctx_p, topdict, key, strlen(key), &val)) < 0)
        return code;
    if ((code = dict_find_string(topdict, key, fontdict)) == 0)
        return_error(e_undefined);
    return code;
}
