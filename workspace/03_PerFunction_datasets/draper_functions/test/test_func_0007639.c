object_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    int err = 0;
    if (excess_args(args, kwds)) {
        if (type->tp_new != object_new &&
            type->tp_init != object_init)
        {
            err = PyErr_WarnEx(PyExc_DeprecationWarning,
                       "object() takes no parameters",
                       1);
        }
        else if (type->tp_new != object_new ||
                 type->tp_init == object_init)
        {
            PyErr_SetString(PyExc_TypeError,
                "object() takes no parameters");
            err = -1;
        }
    }
    if (err < 0)
        return NULL;

    if (type->tp_flags & Py_TPFLAGS_IS_ABSTRACT) {
        static PyObject *comma = NULL;
        PyObject *abstract_methods = NULL;
        PyObject *builtins;
        PyObject *sorted;
        PyObject *sorted_methods = NULL;
        PyObject *joined = NULL;
        const char *joined_str;


        abstract_methods = type_abstractmethods(type, NULL);
        if (abstract_methods == NULL)
            goto error;
        builtins = PyEval_GetBuiltins();
        if (builtins == NULL)
            goto error;
        sorted = PyDict_GetItemString(builtins, "sorted");
        if (sorted == NULL)
            goto error;
        sorted_methods = PyObject_CallFunctionObjArgs(sorted,
                                                      abstract_methods,
                                                      NULL);
        if (sorted_methods == NULL)
            goto error;
        if (comma == NULL) {
            comma = PyString_InternFromString(", ");
            if (comma == NULL)
                goto error;
        }
        joined = PyObject_CallMethod(comma, "join",
                                     "O",  sorted_methods);
        if (joined == NULL)
            goto error;
        joined_str = PyString_AsString(joined);
        if (joined_str == NULL)
            goto error;

        PyErr_Format(PyExc_TypeError,
                     "Can't instantiate abstract class %s "
                     "with abstract methods %s",
                     type->tp_name,
                     joined_str);
    error:
        Py_XDECREF(joined);
        Py_XDECREF(sorted_methods);
        Py_XDECREF(abstract_methods);
        return NULL;
    }
    return type->tp_alloc(type, 0);
}
