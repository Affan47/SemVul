dsa_GenerateGlobalRandomBytes(const SECItem * qItem, PRUint8 * dest,
                              unsigned int * destLen, unsigned int maxDestLen)
{
    SECStatus rv;
    SECItem w;
    const PRUint8 * q = qItem->data;
    unsigned int qLen = qItem->len;

    if (*q == 0) {
        ++q;
        --qLen;
    }
    if (maxDestLen < qLen) {


        PORT_SetError(SEC_ERROR_INVALID_ARGS);
        return SECFailure;
    }
    w.data = NULL;
    if (!SECITEM_AllocItem(NULL, &w, 2*qLen)) {
        return SECFailure;
    }
    *destLen = qLen;

    rv = RNG_GenerateGlobalRandomBytes(w.data, w.len);
    if (rv == SECSuccess) {
        rv = fips186Change_ReduceModQForDSA(w.data, q, qLen, dest);
    }

    SECITEM_FreeItem(&w, PR_FALSE);
    return rv;
}
