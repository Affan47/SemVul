rbthash_key_bucket (rbthash_table_t *tbl, void *key, int keylen)
{
        uint32_t        keyhash = 0;
        int             nbucket = 0;

        if ((!tbl) || (!key))
                return NULL;

        keyhash =  tbl->hashfunc (key, keylen);
        gf_log (GF_RBTHASH, GF_LOG_TRACE, "HASH: %u", keyhash);
        nbucket = (keyhash % tbl->numbuckets);
        gf_log (GF_RBTHASH, GF_LOG_TRACE, "BUCKET: %u", nbucket);

        return &tbl->buckets[nbucket];
}
