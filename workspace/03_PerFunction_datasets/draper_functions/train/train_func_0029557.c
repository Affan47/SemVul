_dir_locals(void)
{
    PyObject *names;
    PyObject *locals;

    locals = PyEval_GetLocals();
    if (locals == NULL)
        return NULL;

    names = PyMapping_Keys(locals);
    if (!names)
        return NULL;
    if (!PyList_Check(names)) {
        PyErr_Format(PyExc_TypeError,
            "dir(): expected keys() of locals to be a list, "
            "not '%.200s'", Py_TYPE(names)->tp_name);
        Py_DECREF(names);
        return NULL;
    }
    if (PyList_Sort(names)) {
        Py_DECREF(names);
        return NULL;
    }

    return names;
}
