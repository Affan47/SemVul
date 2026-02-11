v2i_ASN1_BIT_STRING(X509V3_EXT_METHOD *method,
	     X509V3_CTX *ctx, STACK_OF(CONF_VALUE) *nval)
{
	CONF_VALUE *val;
	ASN1_BIT_STRING *bs;
	int i;
	BIT_STRING_BITNAME *bnam;
	if(!(bs = M_ASN1_BIT_STRING_new())) {
		X509V3err(X509V3_F_V2I_ASN1_BIT_STRING,ERR_R_MALLOC_FAILURE);
		return NULL;
	}
	for(i = 0; i < sk_CONF_VALUE_num(nval); i++) {
		val = sk_CONF_VALUE_value(nval, i);
		for(bnam = method->usr_data; bnam->lname; bnam++) {
			if(!strcmp(bnam->sname, val->name) ||
				!strcmp(bnam->lname, val->name) ) {
				if(!ASN1_BIT_STRING_set_bit(bs, bnam->bitnum, 1)) {
					X509V3err(X509V3_F_V2I_ASN1_BIT_STRING,
						ERR_R_MALLOC_FAILURE);
					M_ASN1_BIT_STRING_free(bs);
					return NULL;
				}
				break;
			}
		}
		if(!bnam->lname) {
			X509V3err(X509V3_F_V2I_ASN1_BIT_STRING,
					X509V3_R_UNKNOWN_BIT_STRING_ARGUMENT);
			X509V3_conf_err(val);
			M_ASN1_BIT_STRING_free(bs);
			return NULL;
		}
	}
	return bs;
}
