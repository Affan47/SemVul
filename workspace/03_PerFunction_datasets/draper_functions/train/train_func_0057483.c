encode_obj_entry(void *ctx, const char *key, k5_json_value value)
{
    struct obj_ctx *j = ctx;

    if (j->ret)
        return;
    if (j->first)
        j->first = 0;
    else
        k5_buf_add(j->buf, ",");
    encode_string(j->buf, key);
    k5_buf_add(j->buf, ":");
    j->ret = encode_value(j->buf, value);
}
