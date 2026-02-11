RSA_HashSign(SECOidTag hashOid, NSSLOWKEYPrivateKey *key,
             unsigned char *sig, unsigned int *sigLen, unsigned int maxLen,
             const unsigned char *hash, unsigned int hashLen)
{
    SECStatus rv = SECFailure;
    SECItem digder;
    PLArenaPool *arena = NULL;
    SGNDigestInfo *di = NULL;

    digder.data = NULL;

    arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    if (!arena) {
        goto loser;
    }


    di = SGN_CreateDigestInfo(hashOid, hash, hashLen);
    if (!di) {
        goto loser;
    }


    rv = DER_Encode(arena, &digder, SGNDigestInfoTemplate, di);
    if (rv != SECSuccess) {
        goto loser;
    }


    rv = RSA_Sign(&key->u.rsa, sig, sigLen, maxLen, digder.data,
                  digder.len);
    if (rv != SECSuccess && PORT_GetError() == SEC_ERROR_LIBRARY_FAILURE) {
        sftk_fatalError = PR_TRUE;
    }

  loser:
    SGN_DestroyDigestInfo(di);
    if (arena != NULL) {
        PORT_FreeArena(arena, PR_FALSE);
    }
    return rv;
}
