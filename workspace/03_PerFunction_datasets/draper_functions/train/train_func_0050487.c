Init_ossl_dh()
{
#if 0
    mOSSL = rb_define_module("OpenSSL");
    mPKey = rb_define_module_under(mOSSL, "PKey");
#endif


    eDHError = rb_define_class_under(mPKey, "DHError", ePKeyError);


    cDH = rb_define_class_under(mPKey, "DH", cPKey);
    rb_define_singleton_method(cDH, "generate", ossl_dh_s_generate, -1);
    rb_define_method(cDH, "initialize", ossl_dh_initialize, -1);
    rb_define_method(cDH, "public?", ossl_dh_is_public, 0);
    rb_define_method(cDH, "private?", ossl_dh_is_private, 0);
    rb_define_method(cDH, "to_text", ossl_dh_to_text, 0);
    rb_define_method(cDH, "export", ossl_dh_export, 0);
    rb_define_alias(cDH, "to_pem", "export");
    rb_define_alias(cDH, "to_s", "export");
    rb_define_method(cDH, "to_der", ossl_dh_to_der, 0);
    rb_define_method(cDH, "public_key", ossl_dh_to_public_key, 0);
    rb_define_method(cDH, "params_ok?", ossl_dh_check_params, 0);
    rb_define_method(cDH, "generate_key!", ossl_dh_generate_key, 0);
    rb_define_method(cDH, "compute_key", ossl_dh_compute_key, 1);

    DEF_OSSL_PKEY_BN(cDH, dh, p);
    DEF_OSSL_PKEY_BN(cDH, dh, g);
    DEF_OSSL_PKEY_BN(cDH, dh, pub_key);
    DEF_OSSL_PKEY_BN(cDH, dh, priv_key);
    rb_define_method(cDH, "params", ossl_dh_get_params, 0);

    OSSL_DEFAULT_DH_512 = ossl_create_dh(
	DEFAULT_DH_512_PRIM, sizeof(DEFAULT_DH_512_PRIM),
	DEFAULT_DH_512_GEN, sizeof(DEFAULT_DH_512_GEN));
    OSSL_DEFAULT_DH_1024 = ossl_create_dh(
	DEFAULT_DH_1024_PRIM, sizeof(DEFAULT_DH_1024_PRIM),
	DEFAULT_DH_1024_GEN, sizeof(DEFAULT_DH_1024_GEN));
}
