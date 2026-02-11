int_div(PyIntObject *x, PyIntObject *y)
{
    long xi, yi;
    long d, m;
    CONVERT_TO_LONG(x, xi);
    CONVERT_TO_LONG(y, yi);
    switch (i_divmod(xi, yi, &d, &m)) {
    case DIVMOD_OK:
        return PyInt_FromLong(d);
    case DIVMOD_OVERFLOW:
        return PyLong_Type.tp_as_number->nb_divide((PyObject *)x,
                                                   (PyObject *)y);
    default:
        return NULL;
    }
}
