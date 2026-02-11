X509V3_EXT_add_nconf(CONF *conf, X509V3_CTX *ctx, char *section,
			 X509 *cert)
	{
	STACK_OF(X509_EXTENSION) **sk = NULL;
	if (cert)
		sk = &cert->cert_info->extensions;
	return X509V3_EXT_add_nconf_sk(conf, ctx, section, sk);
	}
