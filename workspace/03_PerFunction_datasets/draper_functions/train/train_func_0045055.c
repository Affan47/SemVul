Trspi_Verify(UINT32 HashType, BYTE *pHash, UINT32 iHashLength,
	     unsigned char *pModulus, int iKeyLength,
	     BYTE *pSignature, UINT32 sig_len)
{
	int rv, nid;
	unsigned char exp[] = { 0x01, 0x00, 0x01 };
	unsigned char buf[256];
	RSA *rsa = RSA_new();

	if (rsa == NULL) {
		rv = TSPERR(TSS_E_OUTOFMEMORY);
		goto err;
	}


	switch (HashType) {
		case TSS_HASH_SHA1:
			nid = NID_sha1;
			break;
		case TSS_HASH_OTHER:
			nid = NID_undef;
			break;
		default:
			rv = TSPERR(TSS_E_BAD_PARAMETER);
			goto out;
			break;
	}


	rsa->n = BN_bin2bn(pModulus, iKeyLength, rsa->n);

	rsa->e = BN_bin2bn(exp, sizeof(exp), rsa->e);

	if (rsa->n == NULL || rsa->e == NULL) {
		rv = TSPERR(TSS_E_OUTOFMEMORY);
		goto err;
	}


	if (nid == NID_undef) {
		rv = RSA_public_decrypt(sig_len, pSignature, buf, rsa, RSA_PKCS1_PADDING);
		if ((UINT32)rv != iHashLength) {
			rv = TSPERR(TSS_E_FAIL);
			goto out;
		} else if (memcmp(pHash, buf, iHashLength)) {
			rv = TSPERR(TSS_E_FAIL);
			goto out;
		}
	} else {
		if ((rv = RSA_verify(nid, pHash, iHashLength, pSignature, sig_len, rsa)) == 0) {
			rv = TSPERR(TSS_E_FAIL);
			goto out;
		}
	}

	rv = TSS_SUCCESS;
	goto out;

err:
	DEBUG_print_openssl_errors();
out:
	if (rsa)
		RSA_free(rsa);
        return rv;
}
