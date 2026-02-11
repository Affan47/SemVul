builtin_next(PyObject *self, PyObject *args)
{
    PyObject *it, *res;
    PyObject *def = NULL;

    if (!PyArg_UnpackTuple(args, "next", 1, 2, &it, &def))
        return NULL;
    if (!PyIter_Check(it)) {
        PyErr_Format(PyExc_TypeError,
            "%.200s object is not an iterator",
            it->ob_type->tp_name);
        return NULL;
    }

    res = (*it->ob_type->tp_iternext)(it);
    if (res != NULL) {
        return res;
    } else if (def != NULL) {
        if (PyErr_Occurred()) {
            if (!PyErr_ExceptionMatches(PyExc_StopIteration))
                return NULL;
            PyErr_Clear();
        }
        Py_INCREF(def);
        return def;
    } else if (PyErr_Occurred()) {
        return NULL;
    } else {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }
}
