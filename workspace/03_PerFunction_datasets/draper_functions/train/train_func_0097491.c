_PyLong_New(Py_ssize_t size)
{
    if (size > (Py_ssize_t)MAX_LONG_DIGITS) {
        PyErr_SetString(PyExc_OverflowError,
                        "too many digits in integer");
        return NULL;
    }


    return PyObject_NEW_VAR(PyLongObject, &PyLong_Type, size);
}
