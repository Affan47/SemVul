mm_rsa_PEM_read_key(PyObject *self, PyObject *args, PyObject *kwdict)
{
        static char *kwlist[] = { "file", "public", "password", NULL };
        PyObject *pyfile;
        int public, passwordlen=0;
        char *password=NULL;

        RSA *rsa;
        FILE *file;

        if (!PyArg_ParseTupleAndKeywords(args, kwdict,
                                         "O!i|s#:rsa_PEM_read_key",
                                         kwlist, &PyFile_Type, &pyfile,
                                         &public,
                                         &password, &passwordlen))
                return NULL;
        if (!(file = PyFile_AsFile(pyfile))) {
                TYPE_ERR("Invalid file object");
                return NULL;
        }
        if (!passwordlen)
                password = "";

        Py_BEGIN_ALLOW_THREADS
        if (public) {
                rsa = PEM_read_RSAPublicKey(file, NULL, NULL, NULL);
        } else {
                rsa = PEM_read_RSAPrivateKey(file, NULL,
                                             NULL, password);
        }
        Py_END_ALLOW_THREADS

        if (!rsa) {
                mm_SSL_ERR(1);
                return NULL;
        }

        return mm_RSA_new(rsa);
}
