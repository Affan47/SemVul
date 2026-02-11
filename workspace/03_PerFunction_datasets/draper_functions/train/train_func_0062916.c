ossl_x509stctx_get_chain(VALUE self)
{
    X509_STORE_CTX *ctx;
    STACK_OF(X509) *chain;
    X509 *x509;
    int i, num;
    VALUE ary;

    GetX509StCtx(self, ctx);
    if((chain = X509_STORE_CTX_get_chain(ctx)) == NULL){
        return Qnil;
    }
    if((num = sk_X509_num(chain)) < 0){
	OSSL_Debug("certs in chain < 0???");
	return rb_ary_new();
    }
    ary = rb_ary_new2(num);
    for(i = 0; i < num; i++) {
	x509 = sk_X509_value(chain, i);
	rb_ary_push(ary, ossl_x509_new(x509));
    }

    return ary;
}
