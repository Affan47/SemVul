getPrivateDictionary(PyObject *self, PyObject *args) {
    PyObject *data;

    data = PyDict_GetItemString(private_data, current_context->script);
    if (!data) {
        data = PyDict_New();
        PyDict_SetItemString(private_data, current_context->script, data);
        Py_DECREF(data);
    }
    Py_INCREF(data);
    return data;
}
