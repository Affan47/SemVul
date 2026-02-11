SEC_PKCS7ContentIsEncrypted(SEC_PKCS7ContentInfo *cinfo)
{
    SECOidTag kind;

    kind = SEC_PKCS7ContentType (cinfo);
    switch (kind) {
      default:
      case SEC_OID_PKCS7_DATA:
      case SEC_OID_PKCS7_DIGESTED_DATA:
      case SEC_OID_PKCS7_SIGNED_DATA:
	return PR_FALSE;
      case SEC_OID_PKCS7_ENCRYPTED_DATA:
      case SEC_OID_PKCS7_ENVELOPED_DATA:
      case SEC_OID_PKCS7_SIGNED_ENVELOPED_DATA:
	return PR_TRUE;
    }
}
