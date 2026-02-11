delta_divide(PyObject *left, PyObject *right)
{
    PyObject *result = Py_NotImplemented;

    if (PyDelta_Check(left)) {

        if (PyLong_Check(right))
            result = divide_timedelta_int(
                            (PyDateTime_Delta *)left,
                            right);
        else if (PyDelta_Check(right))
            result = divide_timedelta_timedelta(
                            (PyDateTime_Delta *)left,
                            (PyDateTime_Delta *)right);
    }

    if (result == Py_NotImplemented)
        Py_INCREF(result);
    return result;
}
