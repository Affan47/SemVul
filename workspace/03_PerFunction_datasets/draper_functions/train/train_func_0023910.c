PKCS7_add1_attrib_digest(PKCS7_SIGNER_INFO *si,
				const unsigned char *md, int mdlen)
	{
	ASN1_OCTET_STRING *os;
	os = ASN1_OCTET_STRING_new();
	if (!os)
		return 0;
	if (!ASN1_STRING_set(os, md, mdlen)
		|| !PKCS7_add_signed_attribute(si, NID_pkcs9_messageDigest,
						V_ASN1_OCTET_STRING, os))
		{
		ASN1_OCTET_STRING_free(os);
		return 0;
		}
	return 1;
	}
