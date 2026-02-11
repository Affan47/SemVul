copy_issuer(X509V3_CTX *ctx, GENERAL_NAMES *gens)
{
	GENERAL_NAMES *ialt;
	GENERAL_NAME *gen;
	X509_EXTENSION *ext;
	int i;
	if(ctx && (ctx->flags == CTX_TEST)) return 1;
	if(!ctx || !ctx->issuer_cert) {
		X509V3err(X509V3_F_COPY_ISSUER,X509V3_R_NO_ISSUER_DETAILS);
		goto err;
	}
        i = X509_get_ext_by_NID(ctx->issuer_cert, NID_subject_alt_name, -1);
	if(i < 0) return 1;
        if(!(ext = X509_get_ext(ctx->issuer_cert, i)) ||
                        !(ialt = X509V3_EXT_d2i(ext)) ) {
		X509V3err(X509V3_F_COPY_ISSUER,X509V3_R_ISSUER_DECODE_ERROR);
		goto err;
	}

	for(i = 0; i < sk_GENERAL_NAME_num(ialt); i++) {
		gen = sk_GENERAL_NAME_value(ialt, i);
		if(!sk_GENERAL_NAME_push(gens, gen)) {
			X509V3err(X509V3_F_COPY_ISSUER,ERR_R_MALLOC_FAILURE);
			goto err;
		}
	}
	sk_GENERAL_NAME_free(ialt);

	return 1;

	err:
	return 0;

}
