b_setitem(arrayobject *ap, Py_ssize_t i, PyObject *v)
{
    short x;


    if (!PyArg_Parse(v, "h;array item must be integer", &x))
        return -1;
    else if (x < -128) {
        PyErr_SetString(PyExc_OverflowError,
            "signed char is less than minimum");
        return -1;
    }
    else if (x > 127) {
        PyErr_SetString(PyExc_OverflowError,
            "signed char is greater than maximum");
        return -1;
    }
    if (i >= 0)
        ((char *)ap->ob_item)[i] = (char)x;
    return 0;
}
