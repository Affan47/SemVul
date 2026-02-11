numaHashGetNuma(NUMAHASH  *nahash,
                l_uint32   key)
{
l_int32  bucket;
NUMA    *na;

    PROCNAME("numaHashGetNuma");

    if (!nahash)
        return (NUMA *)ERROR_PTR("nahash not defined", procName, NULL);
    bucket = key % nahash->nbuckets;
    na = nahash->numa[bucket];
    if (na)
        return numaClone(na);
    else
        return NULL;
}
