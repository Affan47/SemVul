methodcaller_call(methodcallerobject *mc, PyObject *args, PyObject *kw)
{
    PyObject *method, *obj, *result;

    if (!PyArg_UnpackTuple(args, "methodcaller", 1, 1, &obj))
        return NULL;
    method = PyObject_GetAttr(obj, mc->name);
    if (method == NULL)
        return NULL;
    result = PyObject_Call(method, mc->args, mc->kwds);
    Py_DECREF(method);
    return result;
}
