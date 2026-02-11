long_divrem(PyLongObject *a, PyLongObject *b,
            PyLongObject **pdiv, PyLongObject **prem)
{
    Py_ssize_t size_a = ABS(Py_SIZE(a)), size_b = ABS(Py_SIZE(b));
    PyLongObject *z;

    if (size_b == 0) {
        PyErr_SetString(PyExc_ZeroDivisionError,
                        "long division or modulo by zero");
        return -1;
    }
    if (size_a < size_b ||
        (size_a == size_b &&
         a->ob_digit[size_a-1] < b->ob_digit[size_b-1])) {

        *pdiv = _PyLong_New(0);
        if (*pdiv == NULL)
            return -1;
        Py_INCREF(a);
        *prem = (PyLongObject *) a;
        return 0;
    }
    if (size_b == 1) {
        digit rem = 0;
        z = divrem1(a, b->ob_digit[0], &rem);
        if (z == NULL)
            return -1;
        *prem = (PyLongObject *) PyLong_FromLong((long)rem);
        if (*prem == NULL) {
            Py_DECREF(z);
            return -1;
        }
    }
    else {
        z = x_divrem(a, b, prem);
        if (z == NULL)
            return -1;
    }


    if ((a->ob_size < 0) != (b->ob_size < 0))
        z->ob_size = -(z->ob_size);
    if (a->ob_size < 0 && (*prem)->ob_size != 0)
        (*prem)->ob_size = -((*prem)->ob_size);
    *pdiv = z;
    return 0;
}
