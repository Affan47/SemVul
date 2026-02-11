cl_update_hash(void *ctx, void *data, size_t sz)
{
    int winres=0;

    if (!(ctx) || !(data))
        return -1;

    EXCEPTION_PREAMBLE
    if (!EVP_DigestUpdate((EVP_MD_CTX *)ctx, data, sz))
        return -1;
    EXCEPTION_POSTAMBLE

    if (winres)
        return -1;

    return 0;
}
