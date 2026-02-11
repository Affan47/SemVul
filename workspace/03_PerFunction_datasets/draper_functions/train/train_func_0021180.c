string_array_lookup(const struct string_array *v, const char *key)
{
    int k, len = v->offset_len;
    const char * base_data = v->buffer->data;
    for (k = 0; k < len; k++)
    {
        int offset = v->offset_data[k];
        if (offset >= 0 && strcmp(base_data + offset, key) == 0)
            return k;
    }
    return (-1);
}
