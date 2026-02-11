mm_TLSSock_read(PyObject *self, PyObject *args, PyObject *kwargs)
{
        static char *kwlist[] = { "size", NULL };
        int n;
        SSL *ssl;
        int r;
        PyObject *res;

        assert(mm_TLSSock_Check(self));
        if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:read", kwlist,
                                         &n))
                return NULL;

        ssl = ((mm_TLSSock*)self)->ssl;

        if (!(res = PyString_FromStringAndSize(NULL, n))) {
                PyErr_NoMemory(); return NULL;
        }

        Py_BEGIN_ALLOW_THREADS
        r = SSL_read(ssl, PyString_AS_STRING(res), n);
        Py_END_ALLOW_THREADS
        if (r > 0) {
                if (r != n && _PyString_Resize(&res,r) < 0) {
                        return NULL;
                }
                return res;
        }
        Py_DECREF(res);
        switch (tls_error(ssl, r, IGNORE_ZERO_RETURN)) {
            case NO_ERROR:
                    Py_INCREF(Py_None);
                    return Py_None;
            case ZERO_RETURN:
                    return PyInt_FromLong(0);
            case ERROR:
            default:
                    return NULL;
        }
}
