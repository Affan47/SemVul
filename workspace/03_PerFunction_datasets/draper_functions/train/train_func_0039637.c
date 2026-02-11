authkey_s2i(struct v3_ext_method*, struct v3_ext_ctx*, char *data)
{
  X509       *cert = (X509 *)data;
  char digest[21];

  ASN1_OCTET_STRING *str = ASN1_OCTET_STRING_new();
  AUTHORITY_KEYID *keyid = AUTHORITY_KEYID_new();

  if (str && keyid) {
    SHA1(cert->cert_info->key->public_key->data,
	 cert->cert_info->key->public_key->length,
	 (unsigned char*)digest);
    ASN1_OCTET_STRING_set(str, (unsigned char*)digest, 20);
    ASN1_OCTET_STRING_free(keyid->keyid);
    keyid->keyid = str;
  }
  else {
    if (str) ASN1_OCTET_STRING_free(str);
    if (keyid) AUTHORITY_KEYID_free(keyid);
    keyid = NULL;
  }
  return keyid;
}
