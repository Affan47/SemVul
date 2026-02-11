faulthandler_env_options(void)
{
    PyObject *xoptions, *key, *module, *res;
    char *p;

    if (!((p = Py_GETENV("PYTHONFAULTHANDLER")) && *p != '\0')) {


        int has_key;

        xoptions = PySys_GetXOptions();
        if (xoptions == NULL)
            return -1;

        key = PyUnicode_FromString("faulthandler");
        if (key == NULL)
            return -1;

        has_key = PyDict_Contains(xoptions, key);
        Py_DECREF(key);
        if (!has_key)
            return 0;
    }

    module = PyImport_ImportModule("faulthandler");
    if (module == NULL) {
        return -1;
    }
    res = _PyObject_CallMethodId(module, &PyId_enable, "");
    Py_DECREF(module);
    if (res == NULL)
        return -1;
    Py_DECREF(res);
    return 0;
}
