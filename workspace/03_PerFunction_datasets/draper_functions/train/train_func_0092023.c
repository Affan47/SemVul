X509_ATTRIBUTE_count(X509_ATTRIBUTE *attr)
{
	if(!attr->single) return sk_ASN1_TYPE_num(attr->value.set);
	if(attr->value.single) return 1;
	return 0;
}
