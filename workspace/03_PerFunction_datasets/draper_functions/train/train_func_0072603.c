ASN1_TYPE_get_octetstring(ASN1_TYPE *a, unsigned char *data,
	     int max_len)
	{
	int ret,num;
	unsigned char *p;

	if ((a->type != V_ASN1_OCTET_STRING) || (a->value.octet_string == NULL))
		{
		ASN1err(ASN1_F_ASN1_TYPE_GET_OCTETSTRING,ASN1_R_DATA_IS_WRONG);
		return(-1);
		}
	p=M_ASN1_STRING_data(a->value.octet_string);
	ret=M_ASN1_STRING_length(a->value.octet_string);
	if (ret < max_len)
		num=ret;
	else
		num=max_len;
	memcpy(data,p,num);
	return(ret);
	}
