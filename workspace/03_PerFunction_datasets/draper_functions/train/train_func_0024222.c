check(Crypt_SMIME this, char* signed_mime) {
    BIO* inbuf;
    BIO* detached = NULL;
    BIO* outbuf;
    PKCS7* sign;
    int flags = 0;
    int err;
    BUF_MEM* bufmem;
    SV* result;

    inbuf = BIO_new_mem_buf(signed_mime, -1);
    if (inbuf == NULL) {
	return NULL;
    }

    sign = SMIME_read_PKCS7(inbuf, &detached);
    BIO_free(inbuf);

    if (sign == NULL) {
	return NULL;
    }

    outbuf = BIO_new(BIO_s_mem());
    if (outbuf == NULL) {
	PKCS7_free(sign);
	return NULL;
    }

    err = PKCS7_verify(sign, NULL, this->pubkeys_store, detached, outbuf, flags);
    PKCS7_free(sign);

    if (detached != NULL) {
	BIO_free(detached);
    }

    if (err <= 0) {
	BIO_free(outbuf);
	return NULL;
    }

    BIO_get_mem_ptr(outbuf, &bufmem);
    result = newSVpv(bufmem->data, bufmem->length);
    BIO_free(outbuf);

    return result;
}
