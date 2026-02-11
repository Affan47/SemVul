GCM_DecryptUpdate(GCMContext *gcm, unsigned char *outbuf,
		unsigned int *outlen, unsigned  int maxout,
		const unsigned char *inbuf, unsigned int inlen,
		unsigned int blocksize)
{
    SECStatus rv;
    unsigned int tagBytes;
    unsigned char tag[MAX_BLOCK_SIZE];
    const unsigned char *intag;
    unsigned int len;

    tagBytes = (gcm->tagBits + (PR_BITS_PER_BYTE-1)) / PR_BITS_PER_BYTE;


    if (inlen < tagBytes) {
	PORT_SetError(SEC_ERROR_INPUT_LEN);
	return SECFailure;
    }

    inlen -= tagBytes;
    intag = inbuf + inlen;


    rv = gcmHash_Update(&gcm->ghash_context, inbuf, inlen, blocksize);
    if (rv != SECSuccess) {
	return SECFailure;
    }
    rv = gcm_GetTag(gcm, tag, &len, blocksize, blocksize);
    if (rv != SECSuccess) {
	return SECFailure;
    }


    if (NSS_SecureMemcmp(tag, intag, tagBytes) != 0) {

	PORT_SetError(SEC_ERROR_BAD_DATA);
	return SECFailure;
    }

    return CTR_Update(&gcm->ctr_context, outbuf, outlen, maxout,
			  inbuf, inlen, blocksize);
}
