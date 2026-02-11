time_strptime(PyObject *self, PyObject *args)
{
    PyObject *strptime_module = PyImport_ImportModuleNoBlock("_strptime");
    PyObject *strptime_result;

    if (!strptime_module)
        return NULL;
    strptime_result = PyObject_CallMethod(strptime_module,
                                            "_strptime_time", "O", args);
    Py_DECREF(strptime_module);
    return strptime_result;
}
