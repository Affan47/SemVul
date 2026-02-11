TLSv1_1_server_method(void)
    {
        SSL_METHOD* method = (SSL_METHOD*) XMALLOC(sizeof(SSL_METHOD), 0,
                                                   DYNAMIC_TYPE_METHOD);
        if (method) {
            InitSSL_Method(method, MakeTLSv1_1());
            method->side = SERVER_END;
        }
        return method;
    }
