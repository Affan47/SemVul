ossl_ocspres_get_basic(VALUE self)
{
    OCSP_RESPONSE *res;
    OCSP_BASICRESP *bs;
    VALUE ret;

    GetOCSPRes(self, res);
    if(!(bs = OCSP_response_get1_basic(res)))
	return Qnil;
    WrapOCSPBasicRes(cOCSPBasicRes, ret, bs);

    return ret;
}
