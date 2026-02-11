meh_update_hash(MehHash hash, const unsigned char* data, size_t len)
{
    if (NULL == hash || NULL == data)
        return meh_error("invalid argument passed to meh_update_hash",
                         MEH_INVALID_ARGUMENT);

    if (0 == len)
        return MEH_OK;

    switch (hash->id)
    {
        case MEH_MD5: meh_update_md5(hash->state.md5, data, len); break;
        case MEH_SHA1: meh_update_sha1(hash->state.sha1, data, len); break;
        case MEH_SHA224:
            meh_update_sha224(hash->state.sha224, data, len); break;
        case MEH_SHA256:
            meh_update_sha256(hash->state.sha256, data, len); break;
        case MEH_SHA384:
            meh_update_sha384(hash->state.sha384, data, len); break;
        case MEH_SHA512:
            meh_update_sha512(hash->state.sha512, data, len); break;
        default:
            return meh_error("invalid hash id passed to meh_update_hash",
                             MEH_INVALID_HASH);
    }

    return MEH_OK;
}
