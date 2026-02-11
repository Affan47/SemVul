ossl_sslctx_session_remove_cb(SSL_CTX *ctx, SSL_SESSION *sess)
{
    VALUE ary, sslctx_obj, sess_obj, ret_obj;
    void *ptr;
    int state = 0;

    OSSL_Debug("SSL SESSION remove callback entered");

    if ((ptr = SSL_CTX_get_ex_data(ctx, ossl_ssl_ex_ptr_idx)) == NULL)
    	return;
    sslctx_obj = (VALUE)ptr;
    sess_obj = rb_obj_alloc(cSSLSession);
    CRYPTO_add(&sess->references, 1, CRYPTO_LOCK_SSL_SESSION);
    DATA_PTR(sess_obj) = sess;

    ary = rb_ary_new2(2);
    rb_ary_push(ary, sslctx_obj);
    rb_ary_push(ary, sess_obj);

    ret_obj = rb_protect((VALUE(*)_((VALUE)))ossl_call_session_remove_cb, ary, &state);
    if (state) {


    }
}
