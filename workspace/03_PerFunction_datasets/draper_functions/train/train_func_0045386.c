meh_hash_block_size(MehHash hash)
{
    switch (hash->id)
    {
        case MEH_MD5: return MEH_MD5_BLOCK_SIZE;
        case MEH_SHA1: return MEH_SHA1_BLOCK_SIZE;
        case MEH_SHA224: return MEH_SHA224_BLOCK_SIZE;
        case MEH_SHA256: return MEH_SHA256_BLOCK_SIZE;
        case MEH_SHA384: return MEH_SHA384_BLOCK_SIZE;
        case MEH_SHA512: return MEH_SHA512_BLOCK_SIZE;
        default:
            return meh_error(
                "invalid hash id passed to meh_hash_block_size", -1);
    }

    return -1;
}
