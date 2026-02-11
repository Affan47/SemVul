ossl_pkcs7_get_type(VALUE self)
{
    PKCS7 *p7;

    GetPKCS7(self, p7);
    if(PKCS7_type_is_signed(p7))
	return ID2SYM(rb_intern("signed"));
    if(PKCS7_type_is_encrypted(p7))
	return ID2SYM(rb_intern("encrypted"));
    if(PKCS7_type_is_enveloped(p7))
	return ID2SYM(rb_intern("enveloped"));
    if(PKCS7_type_is_signedAndEnveloped(p7))
	return ID2SYM(rb_intern("signedAndEnveloped"));
    if(PKCS7_type_is_data(p7))
	return ID2SYM(rb_intern("data"));
    return Qnil;
}
