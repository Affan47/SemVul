vfy_VerifyDigest(const SECItem *digest, const SECKEYPublicKey *key,
		 const SECItem *sig, SECOidTag encAlg, SECOidTag hashAlg,
		 void *wincx)
{
    SECStatus rv;
    VFYContext *cx;
    SECItem dsasig;

    rv = SECFailure;

    cx = vfy_CreateContext(key, sig, encAlg, hashAlg, NULL, wincx);
    if (cx != NULL) {
	switch (key->keyType) {
	case rsaKey:
	    if ((digest->len != cx->rsadigestlen) ||
		PORT_Memcmp(digest->data, cx->u.buffer, digest->len)) {
		PORT_SetError(SEC_ERROR_BAD_SIGNATURE);
	    } else {
		rv = SECSuccess;
	    }
	    break;
	case dsaKey:
	case ecKey:
	    dsasig.data = cx->u.buffer;
	    dsasig.len = SECKEY_SignatureLen(cx->key);
	    if (dsasig.len == 0) {
		break;
	    }
	    if (PK11_Verify(cx->key, &dsasig, (SECItem *)digest, cx->wincx)
		!= SECSuccess) {
		PORT_SetError(SEC_ERROR_BAD_SIGNATURE);
	    } else {
		rv = SECSuccess;
	    }
	    break;
	default:
	    break;
	}
	VFY_DestroyContext(cx, PR_TRUE);
    }
    return rv;
}
