PKCS12_unpack_authsafes(PKCS12 *p12)
{
	if (!PKCS7_type_is_data(p12->authsafes))
		{
		PKCS12err(PKCS12_F_PKCS12_UNPACK_AUTHSAFES,PKCS12_R_CONTENT_TYPE_NOT_DATA);
		return NULL;
		}
	return ASN1_item_unpack(p12->authsafes->d.data, ASN1_ITEM_rptr(PKCS12_AUTHSAFES));
}
