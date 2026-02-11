struct_init (PyObject *self, PyObject *args, PyObject *kw)
{
    StructObject * const that =  (StructObject *) self;
    that->dict = NULL;
    that->repr = NULL;

    if (args && !PyArg_ParseTuple (args, ""))
        return -1;

    if (kw == NULL || PyDict_Size (kw) == 0) {
        PyErr_SetString (PyExc_ValueError, "Struct is empty");
        return -1;
    }


    that->dict = PyDict_Copy (kw);

    return 0;
}
