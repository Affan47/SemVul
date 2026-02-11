common_EncodeDerSig(SECItem *dest, SECItem *src)
{
    SECItem *         item;
    SECItem           srcItem;
    DSA_ASN1Signature sig;
    unsigned char     *signedR;
    unsigned char     *signedS;
    unsigned int len;


    len = src->len/2;
    signedR = (unsigned char *) PORT_Alloc(len + 1);
    if (!signedR) return SECFailure;
    signedS = (unsigned char *) PORT_ZAlloc(len + 1);
    if (!signedS) {
        if (signedR) PORT_Free(signedR);
	return SECFailure;
    }

    PORT_Memset(&sig, 0, sizeof(sig));


    sig.r.type = siUnsignedInteger;
    sig.r.data = signedR;
    sig.r.len  = sizeof signedR;
    sig.s.type = siUnsignedInteger;
    sig.s.data = signedS;
    sig.s.len  = sizeof signedR;

    srcItem.data = src->data;
    srcItem.len  = len;

    DSAU_ConvertUnsignedToSigned(&sig.r, &srcItem);
    srcItem.data += len;
    DSAU_ConvertUnsignedToSigned(&sig.s, &srcItem);

    item = SEC_ASN1EncodeItem(NULL, dest, &sig, DSA_SignatureTemplate);
    if (signedR) PORT_Free(signedR);
    if (signedS) PORT_Free(signedS);
    if (item == NULL)
	return SECFailure;


    return SECSuccess;
}
