float_dealloc(PyFloatObject *op)
{
    if (PyFloat_CheckExact(op)) {
        if (numfree >= PyFloat_MAXFREELIST)  {
            PyObject_FREE(op);
            return;
        }
        numfree++;
        Py_TYPE(op) = (struct _typeobject *)free_list;
        free_list = op;
    }
    else
        Py_TYPE(op)->tp_free((PyObject *)op);
}
