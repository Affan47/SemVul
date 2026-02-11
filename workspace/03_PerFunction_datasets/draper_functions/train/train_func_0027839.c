ssl3_ComputeCommonKeyHash(SECOidTag hashAlg,
			  PRUint8 * hashBuf, unsigned int bufLen,
			  SSL3Hashes *hashes, PRBool bypassPKCS11)
{
    SECStatus     rv 		= SECSuccess;

#ifndef NO_PKCS11_BYPASS
    if (bypassPKCS11) {
	if (hashAlg == SEC_OID_UNKNOWN) {
	    MD5_HashBuf (hashes->u.s.md5, hashBuf, bufLen);
	    SHA1_HashBuf(hashes->u.s.sha, hashBuf, bufLen);
	    hashes->len = MD5_LENGTH + SHA1_LENGTH;
	} else if (hashAlg == SEC_OID_SHA1) {
	    SHA1_HashBuf(hashes->u.raw, hashBuf, bufLen);
	    hashes->len = SHA1_LENGTH;
	} else if (hashAlg == SEC_OID_SHA256) {
	    SHA256_HashBuf(hashes->u.raw, hashBuf, bufLen);
	    hashes->len = SHA256_LENGTH;
	} else if (hashAlg == SEC_OID_SHA384) {
	    SHA384_HashBuf(hashes->u.raw, hashBuf, bufLen);
	    hashes->len = SHA384_LENGTH;
	} else if (hashAlg == SEC_OID_SHA512) {
	    SHA512_HashBuf(hashes->u.raw, hashBuf, bufLen);
	    hashes->len = SHA512_LENGTH;
	} else {
	    PORT_SetError(SSL_ERROR_UNSUPPORTED_HASH_ALGORITHM);
	    return SECFailure;
	}
    } else
#endif
    {
	if (hashAlg == SEC_OID_UNKNOWN) {
	    rv = PK11_HashBuf(SEC_OID_MD5, hashes->u.s.md5, hashBuf, bufLen);
	    if (rv != SECSuccess) {
		ssl_MapLowLevelError(SSL_ERROR_MD5_DIGEST_FAILURE);
		rv = SECFailure;
		goto done;
	    }

	    rv = PK11_HashBuf(SEC_OID_SHA1, hashes->u.s.sha, hashBuf, bufLen);
	    if (rv != SECSuccess) {
		ssl_MapLowLevelError(SSL_ERROR_SHA_DIGEST_FAILURE);
		rv = SECFailure;
	    }
	    hashes->len = MD5_LENGTH + SHA1_LENGTH;
	} else {
	    hashes->len = HASH_ResultLenByOidTag(hashAlg);
	    if (hashes->len > sizeof(hashes->u.raw)) {
		ssl_MapLowLevelError(SSL_ERROR_UNSUPPORTED_HASH_ALGORITHM);
		rv = SECFailure;
		goto done;
	    }
	    rv = PK11_HashBuf(hashAlg, hashes->u.raw, hashBuf, bufLen);
	    if (rv != SECSuccess) {
		ssl_MapLowLevelError(SSL_ERROR_DIGEST_FAILURE);
		rv = SECFailure;
	    }
	}
    }
    hashes->hashAlg = hashAlg;

done:
    return rv;
}
