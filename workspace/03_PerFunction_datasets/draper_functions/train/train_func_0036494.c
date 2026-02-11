PK11_HashBuf(SECOidTag hashAlg, unsigned char *out, const unsigned char *in,
								PRInt32 len) {
    PK11Context *context;
    unsigned int max_length;
    unsigned int out_length;
    SECStatus rv;


    if (len < 0) {
        PORT_SetError(SEC_ERROR_INVALID_ARGS);
        return SECFailure;
    }

    context = PK11_CreateDigestContext(hashAlg);
    if (context == NULL) return SECFailure;

    rv = PK11_DigestBegin(context);
    if (rv != SECSuccess) {
	PK11_DestroyContext(context, PR_TRUE);
	return rv;
    }

    rv = PK11_DigestOp(context, in, len);
    if (rv != SECSuccess) {
	PK11_DestroyContext(context, PR_TRUE);
	return rv;
    }


    max_length = HASH_ResultLenByOidTag(hashAlg);
    PORT_Assert(max_length);
    if (!max_length)
    	max_length = HASH_LENGTH_MAX;

    rv = PK11_DigestFinal(context,out,&out_length,max_length);
    PK11_DestroyContext(context, PR_TRUE);
    return rv;
}
