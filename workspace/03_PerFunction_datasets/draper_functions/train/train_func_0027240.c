i2s_ASN1_ENUMERATED(X509V3_EXT_METHOD *method, ASN1_ENUMERATED *a)
{
	BIGNUM *bntmp = NULL;
	char *strtmp = NULL;
	if(!a) return NULL;
	if(!(bntmp = ASN1_ENUMERATED_to_BN(a, NULL)) ||
	    !(strtmp = BN_bn2dec(bntmp)) )
		X509V3err(X509V3_F_I2S_ASN1_ENUMERATED,ERR_R_MALLOC_FAILURE);
	BN_free(bntmp);
	return strtmp;
}
