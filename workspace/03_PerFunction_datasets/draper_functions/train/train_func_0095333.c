ossl_default_tmp_dh_callback(SSL *ssl, int is_export, int keylength)
{
    rb_warning("using default DH parameters.");

    switch(keylength){
    case 512:
	return OSSL_DEFAULT_DH_512;
    case 1024:
	return OSSL_DEFAULT_DH_1024;
    }
    return NULL;
}
