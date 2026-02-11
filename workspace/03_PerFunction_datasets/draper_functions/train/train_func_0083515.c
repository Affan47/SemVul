sftk_fips_HMAC(unsigned char *hmac_computed,
               const PRUint8 *secret_key,
               unsigned int secret_key_length,
               const PRUint8 *message,
               unsigned int message_length,
               HASH_HashType hashAlg )
{
    SECStatus hmac_status = SECFailure;
    HMACContext *cx = NULL;
    SECHashObject *hashObj = NULL;
    unsigned int bytes_hashed = 0;

    hashObj = (SECHashObject *) HASH_GetRawHashObject(hashAlg);

    if (!hashObj)
        return( SECFailure );

    cx = HMAC_Create(hashObj, secret_key,
                     secret_key_length,
                     PR_TRUE);

    if (cx == NULL)
        return( SECFailure );

    HMAC_Begin(cx);
    HMAC_Update(cx, message, message_length);
    hmac_status = HMAC_Finish(cx, hmac_computed, &bytes_hashed,
                              hashObj->length);

    HMAC_Destroy(cx, PR_TRUE);

    return( hmac_status );
}
