mm_RSA_get_exponent(PyObject *self, PyObject *args, PyObject *kwdict)
{

        static char *kwlist[] = {  NULL };

        RSA *rsa;
        PyObject *e;

        assert(mm_RSA_Check(self));
        if (!PyArg_ParseTupleAndKeywords(args, kwdict,
                                         ":get_exponent", kwlist))
                return NULL;

        rsa = ((mm_RSA*)self)->rsa;
        if (!rsa->e) { TYPE_ERR("Key has no e"); return NULL; }
        if (!(e = bn2pylong(rsa->e))) {
                PyErr_NoMemory(); return NULL;
        }
        return e;
}
