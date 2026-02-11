mprLookupKeyEntry(MprHash *hash, cvoid *key)
{
    mprAssert(key);
    mprAssert(hash);

    return lookupHash(0, 0, hash, key);
}
