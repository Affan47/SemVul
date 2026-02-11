read_byte_array(const char** memory, size_t* length)
{
    struct nbt_byte_array ret;
    ret.data = NULL;

    READ_GENERIC(&ret.length, sizeof ret.length, swapped_memscan, goto parse_error);

    if(ret.length < 0) goto parse_error;

    CHECKED_MALLOC(ret.data, ret.length, goto parse_error);

    READ_GENERIC(ret.data, (size_t)ret.length, memscan, goto parse_error);

    return ret;

parse_error:
    if(errno == NBT_OK)
        errno = NBT_ERR;

    free(ret.data);
    ret.data = NULL;
    return ret;
}
