microseconds_to_delta_ex(PyObject *pyus, PyTypeObject *type)
{
    int us;
    int s;
    int d;
    long temp;

    PyObject *tuple = NULL;
    PyObject *num = NULL;
    PyObject *result = NULL;

    tuple = PyNumber_Divmod(pyus, us_per_second);
    if (tuple == NULL)
        goto Done;

    num = PyTuple_GetItem(tuple, 1);
    if (num == NULL)
        goto Done;
    temp = PyLong_AsLong(num);
    num = NULL;
    if (temp == -1 && PyErr_Occurred())
        goto Done;
    assert(0 <= temp && temp < 1000000);
    us = (int)temp;
    if (us < 0) {

        assert(PyErr_Occurred());
        goto Done;
    }

    num = PyTuple_GetItem(tuple, 0);
    if (num == NULL)
        goto Done;
    Py_INCREF(num);
    Py_DECREF(tuple);

    tuple = PyNumber_Divmod(num, seconds_per_day);
    if (tuple == NULL)
        goto Done;
    Py_DECREF(num);

    num = PyTuple_GetItem(tuple, 1);
    if (num == NULL)
        goto Done;
    temp = PyLong_AsLong(num);
    num = NULL;
    if (temp == -1 && PyErr_Occurred())
        goto Done;
    assert(0 <= temp && temp < 24*3600);
    s = (int)temp;

    if (s < 0) {

        assert(PyErr_Occurred());
        goto Done;
    }

    num = PyTuple_GetItem(tuple, 0);
    if (num == NULL)
        goto Done;
    Py_INCREF(num);
    temp = PyLong_AsLong(num);
    if (temp == -1 && PyErr_Occurred())
        goto Done;
    d = (int)temp;
    if ((long)d != temp) {
        PyErr_SetString(PyExc_OverflowError, "normalized days too "
                        "large to fit in a C int");
        goto Done;
    }
    result = new_delta_ex(d, s, us, 0, type);

Done:
    Py_XDECREF(tuple);
    Py_XDECREF(num);
    return result;
}
