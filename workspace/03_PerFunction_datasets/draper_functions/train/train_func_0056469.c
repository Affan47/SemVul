slot_sq_item(PyObject *self, Py_ssize_t i)
{
    PyObject *func, *args = NULL, *ival = NULL, *retval = NULL;
    descrgetfunc f;

    func = _PyType_LookupId(Py_TYPE(self), &PyId___getitem__);
    if (func != NULL) {
        if ((f = Py_TYPE(func)->tp_descr_get) == NULL)
            Py_INCREF(func);
        else {
            func = f(func, self, (PyObject *)(Py_TYPE(self)));
            if (func == NULL) {
                return NULL;
            }
        }
        ival = PyLong_FromSsize_t(i);
        if (ival != NULL) {
            args = PyTuple_New(1);
            if (args != NULL) {
                PyTuple_SET_ITEM(args, 0, ival);
                retval = PyObject_Call(func, args, NULL);
                Py_XDECREF(args);
                Py_XDECREF(func);
                return retval;
            }
        }
    }
    else {
        PyObject *getitem_str = _PyUnicode_FromId(&PyId___getitem__);
        PyErr_SetObject(PyExc_AttributeError, getitem_str);
    }
    Py_XDECREF(args);
    Py_XDECREF(ival);
    Py_XDECREF(func);
    return NULL;
}
