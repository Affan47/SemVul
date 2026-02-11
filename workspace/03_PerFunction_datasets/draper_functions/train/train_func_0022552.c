array_fromunicode(arrayobject *self, PyObject *args)
{
    Py_UNICODE *ustr;
    Py_ssize_t n;

    if (!PyArg_ParseTuple(args, "u#:fromunicode", &ustr, &n))
        return NULL;
    if (self->ob_descr->typecode != 'u') {
        PyErr_SetString(PyExc_ValueError,
            "fromunicode() may only be called on "
            "type 'u' arrays");
        return NULL;
    }
    if (n > 0) {
        Py_UNICODE *item = (Py_UNICODE *) self->ob_item;
        if (Py_SIZE(self) > PY_SSIZE_T_MAX - n) {
            return PyErr_NoMemory();
        }
        PyMem_RESIZE(item, Py_UNICODE, Py_SIZE(self) + n);
        if (item == NULL) {
            PyErr_NoMemory();
            return NULL;
        }
        self->ob_item = (char *) item;
        Py_SIZE(self) += n;
        self->allocated = Py_SIZE(self);
        memcpy(item + Py_SIZE(self) - n,
               ustr, n * sizeof(Py_UNICODE));
    }

    Py_INCREF(Py_None);
    return Py_None;
}
