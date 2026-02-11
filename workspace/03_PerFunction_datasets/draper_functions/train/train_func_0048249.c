ossl_ocspreq_initialize(int argc, VALUE *argv, VALUE self)
{
    VALUE arg;
    const unsigned char *p;

    rb_scan_args(argc, argv, "01", &arg);
    if(!NIL_P(arg)){
	OCSP_REQUEST *req = DATA_PTR(self), *x;
	arg = ossl_to_der_if_possible(arg);
	StringValue(arg);
	p = (unsigned char*)RSTRING_PTR(arg);
	x = d2i_OCSP_REQUEST(&req, &p, RSTRING_LEN(arg));
	DATA_PTR(self) = req;
	if(!x){
	    ossl_raise(eOCSPError, "cannot load DER encoded request");
	}
    }

    return self;
}
