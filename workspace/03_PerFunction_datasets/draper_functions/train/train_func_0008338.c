whichmodule(PyObject *global, PyObject *global_name)
{
    Py_ssize_t i, j;
    static PyObject *module_str = NULL;
    static PyObject *main_str = NULL;
    PyObject *module_name;
    PyObject *modules_dict;
    PyObject *module;
    PyObject *obj;

    if (module_str == NULL) {
        module_str = PyUnicode_InternFromString("__module__");
        if (module_str == NULL)
            return NULL;
        main_str = PyUnicode_InternFromString("__main__");
        if (main_str == NULL)
            return NULL;
    }

    module_name = PyObject_GetAttr(global, module_str);


    if (module_name == Py_None) {
        Py_DECREF(module_name);
        goto search;
    }

    if (module_name) {
        return module_name;
    }
    if (PyErr_ExceptionMatches(PyExc_AttributeError))
        PyErr_Clear();
    else
        return NULL;

  search:
    modules_dict = PySys_GetObject("modules");
    if (modules_dict == NULL)
        return NULL;

    i = 0;
    module_name = NULL;
    while ((j = PyDict_Next(modules_dict, &i, &module_name, &module))) {
        if (PyObject_RichCompareBool(module_name, main_str, Py_EQ) == 1)
            continue;

        obj = PyObject_GetAttr(module, global_name);
        if (obj == NULL) {
            if (PyErr_ExceptionMatches(PyExc_AttributeError))
                PyErr_Clear();
            else
                return NULL;
            continue;
        }

        if (obj != global) {
            Py_DECREF(obj);
            continue;
        }

        Py_DECREF(obj);
        break;
    }


    if (!j) {
        module_name = main_str;
    }

    Py_INCREF(module_name);
    return module_name;
}
