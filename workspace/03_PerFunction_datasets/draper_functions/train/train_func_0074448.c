addToSeedThenHash(HASH_HashType   hashtype,
                  const SECItem * seed,
                  unsigned long   addend,
                  int             seedlen,
                  unsigned char * hashOutBuf)
{
    SECItem str = { 0, 0, 0 };
    SECStatus rv;
    rv = addToSeed(seed, addend, seedlen, &str);
    if (rv != SECSuccess) {
	return rv;
    }
    rv = HASH_HashBuf(hashtype, hashOutBuf, str.data, str.len);
    if (str.data)
	SECITEM_ZfreeItem(&str, PR_FALSE);
    return rv;
}
