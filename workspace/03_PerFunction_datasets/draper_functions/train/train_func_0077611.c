DupPKCS7RecipientPtr(VALUE obj)
{
    PKCS7_RECIP_INFO *p7ri, *pkcs7;

    SafeGetPKCS7ri(obj, p7ri);
    if (!(pkcs7 = PKCS7_RECIP_INFO_dup(p7ri))) {
	ossl_raise(ePKCS7Error, NULL);
    }

    return pkcs7;
}
