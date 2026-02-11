context_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    char *kwlist[] = {"protocol", NULL};
    PySSLContext *self;
    int proto_version = PY_SSL_VERSION_SSL23;
    SSL_CTX *ctx = NULL;

    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "i:_SSLContext", kwlist,
        &proto_version))
        return NULL;

    PySSL_BEGIN_ALLOW_THREADS
    if (proto_version == PY_SSL_VERSION_TLS1)
        ctx = SSL_CTX_new(TLSv1_method());
    else if (proto_version == PY_SSL_VERSION_SSL3)
        ctx = SSL_CTX_new(SSLv3_method());
#ifndef OPENSSL_NO_SSL2
    else if (proto_version == PY_SSL_VERSION_SSL2)
        ctx = SSL_CTX_new(SSLv2_method());
#endif
    else if (proto_version == PY_SSL_VERSION_SSL23)
        ctx = SSL_CTX_new(SSLv23_method());
    else
        proto_version = -1;
    PySSL_END_ALLOW_THREADS

    if (proto_version == -1) {
        PyErr_SetString(PyExc_ValueError,
                        "invalid protocol version");
        return NULL;
    }
    if (ctx == NULL) {
        PyErr_SetString(PySSLErrorObject,
                        "failed to allocate SSL context");
        return NULL;
    }

    assert(type != NULL && type->tp_alloc != NULL);
    self = (PySSLContext *) type->tp_alloc(type, 0);
    if (self == NULL) {
        SSL_CTX_free(ctx);
        return NULL;
    }
    self->ctx = ctx;

    SSL_CTX_set_verify(self->ctx, SSL_VERIFY_NONE, NULL);
    SSL_CTX_set_options(self->ctx,
                        SSL_OP_ALL & ~SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS);

#define SID_CTX "Python"
    SSL_CTX_set_session_id_context(self->ctx, (const unsigned char *) SID_CTX,
                                   sizeof(SID_CTX));
#undef SID_CTX

    return (PyObject *)self;
}
