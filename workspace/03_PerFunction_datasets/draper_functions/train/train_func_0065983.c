PyNumber_AsSsize_t(PyObject *item, PyObject *err)
{
    Py_ssize_t result;
    PyObject *runerr;
    PyObject *value = PyNumber_Index(item);
    if (value == NULL)
        return -1;


    result = PyInt_AsSsize_t(value);
    if (result != -1 || !(runerr = PyErr_Occurred()))
        goto finish;


    if (!PyErr_GivenExceptionMatches(runerr, PyExc_OverflowError))
        goto finish;

    PyErr_Clear();


    if (!err) {
        assert(PyLong_Check(value));


        if (_PyLong_Sign(value) < 0)
            result = PY_SSIZE_T_MIN;
        else
            result = PY_SSIZE_T_MAX;
    }
    else {

        PyErr_Format(err,
                     "cannot fit '%.200s' into an index-sized integer",
                     item->ob_type->tp_name);
    }

 finish:
    Py_DECREF(value);
    return result;
}
