fs_hash_uri_ignore_bnode(const char *str)
{
    uint64_t top;

    if (!str) {
        return 0;
    }

    top = umac_wrapper(str, 0);
    top |= 0xC000000000000000LL;

    return top;
}
