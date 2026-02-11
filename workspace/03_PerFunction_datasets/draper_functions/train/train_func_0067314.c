ossl_ssl_read_internal(int argc, VALUE *argv, VALUE self, int nonblock)
{
    SSL *ssl;
    int ilen, nread = 0;
    VALUE len, str;
    rb_io_t *fptr;

    rb_scan_args(argc, argv, "11", &len, &str);
    ilen = NUM2INT(len);
    if(NIL_P(str)) str = rb_str_new(0, ilen);
    else{
        StringValue(str);
        rb_str_modify(str);
        rb_str_resize(str, ilen);
    }
    if(ilen == 0) return str;

    Data_Get_Struct(self, SSL, ssl);
    GetOpenFile(ossl_ssl_get_io(self), fptr);
    if (ssl) {
	if(!nonblock && SSL_pending(ssl) <= 0)
	    rb_thread_wait_fd(FPTR_TO_FD(fptr));
	for (;;){
	    nread = SSL_read(ssl, RSTRING_PTR(str), RSTRING_LENINT(str));
	    switch(ssl_get_error(ssl, nread)){
	    case SSL_ERROR_NONE:
		goto end;
	    case SSL_ERROR_ZERO_RETURN:
		rb_eof_error();
	    case SSL_ERROR_WANT_WRITE:
                write_would_block(nonblock);
                rb_io_wait_writable(FPTR_TO_FD(fptr));
                continue;
	    case SSL_ERROR_WANT_READ:
                read_would_block(nonblock);
                rb_io_wait_readable(FPTR_TO_FD(fptr));
		continue;
	    case SSL_ERROR_SYSCALL:
		if(ERR_peek_error() == 0 && nread == 0) rb_eof_error();
		rb_sys_fail(0);
	    default:
		ossl_raise(eSSLError, "SSL_read:");
	    }
        }
    }
    else {
        ID meth = nonblock ? rb_intern("read_nonblock") : rb_intern("sysread");
        rb_warning("SSL session is not started yet.");
        return rb_funcall(ossl_ssl_get_io(self), meth, 2, len, str);
    }

  end:
    rb_str_set_len(str, nread);
    OBJ_TAINT(str);

    return str;
}
