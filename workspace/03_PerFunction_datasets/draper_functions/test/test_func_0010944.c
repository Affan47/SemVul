mm_check_oaep_padding(PyObject *self, PyObject *args, PyObject *kwargs)
{
        static char *kwlist[] = { "s", "param", "keylen", NULL };

        const unsigned char *param, *input;
        int paramlen, inputlen;
        int keylen, r;

        PyObject *output;

        if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                         "s#s#i:check_oaep_padding", kwlist,
                                  &input,&inputlen,&param,&paramlen,&keylen))
                return NULL;


        if (inputlen == 0 || *input != '\000') {
                PyErr_SetString(mm_CryptoError, "Bad padding");
                return NULL;
        }

        r = keylen-OAEP_OVERHEAD;
        if (!(output = PyString_FromStringAndSize(NULL, r))) {
                PyErr_NoMemory(); return NULL;
        }

        Py_BEGIN_ALLOW_THREADS
        r = RSA_padding_check_PKCS1_OAEP(PyString_AS_USTRING(output), r,
                                         input+1, inputlen-1, keylen,
                                         param, paramlen);
        Py_END_ALLOW_THREADS
        if (r <= 0) {
                mm_SSL_ERR(1);
                Py_DECREF(output);
                return NULL;
        }
        if(_PyString_Resize(&output, r)) return NULL;

        return output;
}
