__Pyx_PyObject_CallMethodTuple(PyObject* obj, PyObject* method_name, PyObject* args) {
    PyObject *method, *result = NULL;
    if (unlikely(!args)) return NULL;
    method = __Pyx_PyObject_GetAttrStr(obj, method_name);
    if (unlikely(!method)) goto bad;
    result = __Pyx_PyObject_Call(method, args, NULL);
    Py_DECREF(method);
bad:
    Py_DECREF(args);
    return result;
}
