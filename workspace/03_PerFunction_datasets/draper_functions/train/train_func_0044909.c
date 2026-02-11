handle_callback(PyWeakReference *ref, PyObject *callback)
{
    PyObject *cbresult = PyObject_CallFunctionObjArgs(callback, ref, NULL);

    if (cbresult == NULL)
        PyErr_WriteUnraisable(callback);
    else
        Py_DECREF(cbresult);
}
