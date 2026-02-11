_timezone_check_argument(PyObject *dt, const char *meth)
{
    if (dt == Py_None || PyDateTime_Check(dt))
        return 0;
    PyErr_Format(PyExc_TypeError, "%s(dt) argument must be a datetime instance"
                 " or None, not %.200s", meth, Py_TYPE(dt)->tp_name);
    return -1;
}
