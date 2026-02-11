delta_total_seconds(PyObject *self)
{
    PyObject *total_seconds;
    PyObject *total_microseconds;
    PyObject *one_million;

    total_microseconds = delta_to_microseconds((PyDateTime_Delta *)self);
    if (total_microseconds == NULL)
        return NULL;

    one_million = PyLong_FromLong(1000000L);
    if (one_million == NULL) {
        Py_DECREF(total_microseconds);
        return NULL;
    }

    total_seconds = PyNumber_TrueDivide(total_microseconds, one_million);

    Py_DECREF(total_microseconds);
    Py_DECREF(one_million);
    return total_seconds;
}
