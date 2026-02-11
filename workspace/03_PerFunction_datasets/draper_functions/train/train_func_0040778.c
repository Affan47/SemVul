embed_list_includes(const gs_param_string_array *psa, const byte *chars,
                    uint size)
{
    uint i;

    for (i = 0; i < psa->size; ++i)
        if (!bytes_compare(psa->data[i].data, psa->data[i].size, chars, size))
            return true;
    return false;
}
