X509_ATTRIBUTE_get0_data(X509_ATTRIBUTE *attr, int idx,
					int atrtype, void *data)
{
	ASN1_TYPE *ttmp;
	ttmp = X509_ATTRIBUTE_get0_type(attr, idx);
	if(!ttmp) return NULL;
	if(atrtype != ASN1_TYPE_get(ttmp)){
		X509err(X509_F_X509_ATTRIBUTE_GET0_DATA, X509_R_WRONG_TYPE);
		return NULL;
	}
	return ttmp->value.ptr;
}
