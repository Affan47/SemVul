FreeDecodedCert(DecodedCert* cert)
{
    if (cert->subjectCNLen == 0)
        XFREE(cert->subjectCN, cert->heap, DYNAMIC_TYPE_SUBJECT_CN);
    if (cert->pubKeyStored == 1)
        XFREE(cert->publicKey, cert->heap, DYNAMIC_TYPE_PUBLIC_KEY);
}
