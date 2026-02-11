ossl_x509store_verify(int argc, VALUE *argv, VALUE self)
{
    VALUE cert, chain;
    VALUE ctx, proc, result;

    rb_scan_args(argc, argv, "11", &cert, &chain);
    ctx = rb_funcall(cX509StoreContext, rb_intern("new"), 3, self, cert, chain);
    proc = rb_block_given_p() ?  rb_block_proc() :
	   rb_iv_get(self, "@verify_callback");
    rb_iv_set(ctx, "@verify_callback", proc);
    result = rb_funcall(ctx, rb_intern("verify"), 0);

    rb_iv_set(self, "@error", ossl_x509stctx_get_err(ctx));
    rb_iv_set(self, "@error_string", ossl_x509stctx_get_err_string(ctx));
    rb_iv_set(self, "@chain", ossl_x509stctx_get_chain(ctx));

    return result;
}
