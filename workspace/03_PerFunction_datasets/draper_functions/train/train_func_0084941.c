mm_TLSSock_accept(PyObject *self, PyObject *args, PyObject *kwargs)
{
        SSL *ssl;
        int r;

        assert(mm_TLSSock_Check(self));
        FAIL_IF_ARGS();

        ssl = ((mm_TLSSock*)self)->ssl;
        Py_BEGIN_ALLOW_THREADS
        r = SSL_accept(ssl);
        Py_END_ALLOW_THREADS

        if (tls_error(ssl, r, 0))
                return NULL;

        Py_INCREF(Py_None);
        return Py_None;
}
