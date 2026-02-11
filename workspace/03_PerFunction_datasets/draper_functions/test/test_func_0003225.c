PyErr_WriteUnraisable(PyObject *obj)
{
    _Py_IDENTIFIER(__module__);
    PyObject *f, *t, *v, *tb;
    PyObject *moduleName = NULL;
    char* className;

    PyErr_Fetch(&t, &v, &tb);

    f = _PySys_GetObjectId(&PyId_stderr);
    if (f == NULL || f == Py_None)
        goto done;

    if (obj) {
        if (PyFile_WriteString("Exception ignored in: ", f) < 0)
            goto done;
        if (PyFile_WriteObject(obj, f, 0) < 0)
            goto done;
        if (PyFile_WriteString("\n", f) < 0)
            goto done;
    }

    if (PyTraceBack_Print(tb, f) < 0)
        goto done;

    if (!t)
        goto done;

    assert(PyExceptionClass_Check(t));
    className = PyExceptionClass_Name(t);
    if (className != NULL) {
        char *dot = strrchr(className, '.');
        if (dot != NULL)
            className = dot+1;
    }

    moduleName = _PyObject_GetAttrId(t, &PyId___module__);
    if (moduleName == NULL) {
        PyErr_Clear();
        if (PyFile_WriteString("<unknown>", f) < 0)
            goto done;
    }
    else {
        if (_PyUnicode_CompareWithId(moduleName, &PyId_builtins) != 0) {
            if (PyFile_WriteObject(moduleName, f, Py_PRINT_RAW) < 0)
                goto done;
            if (PyFile_WriteString(".", f) < 0)
                goto done;
        }
    }
    if (className == NULL) {
        if (PyFile_WriteString("<unknown>", f) < 0)
            goto done;
    }
    else {
        if (PyFile_WriteString(className, f) < 0)
            goto done;
    }

    if (v && v != Py_None) {
        if (PyFile_WriteString(": ", f) < 0)
            goto done;
        if (PyFile_WriteObject(v, f, Py_PRINT_RAW) < 0)
            goto done;
    }
    if (PyFile_WriteString("\n", f) < 0)
        goto done;

done:
    Py_XDECREF(moduleName);
    Py_XDECREF(t);
    Py_XDECREF(v);
    Py_XDECREF(tb);
    PyErr_Clear();
}
