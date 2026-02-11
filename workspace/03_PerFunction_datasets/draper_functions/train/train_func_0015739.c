vfy_VerifyData(const unsigned char *buf, int len, const SECKEYPublicKey *key,
	       const SECItem *sig, SECOidTag encAlg, SECOidTag hashAlg,
	       SECOidTag *hash, void *wincx)
{
    SECStatus rv;
    VFYContext *cx;

    cx = vfy_CreateContext(key, sig, encAlg, hashAlg, hash, wincx);
    if (cx == NULL)
	return SECFailure;

    rv = VFY_Begin(cx);
    if (rv == SECSuccess) {
	rv = VFY_Update(cx, (unsigned char *)buf, len);
	if (rv == SECSuccess)
	    rv = VFY_End(cx);
    }

    VFY_DestroyContext(cx, PR_TRUE);
    return rv;
}
