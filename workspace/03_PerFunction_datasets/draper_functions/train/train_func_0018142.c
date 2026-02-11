k5_json_string_create_base64(const void *data, size_t len,
                             k5_json_string *val_out)
{
    char *base64;
    int ret;

    *val_out = NULL;
    base64 = k5_base64_encode(data, len);
    if (base64 == NULL)
        return ENOMEM;
    ret = k5_json_string_create(base64, val_out);
    free(base64);
    return ret;
}
