_PyObject_CallMethodIdObjArgs(PyObject *callable,
        struct _Py_Identifier *name, ...)
{
    PyObject *args, *tmp;
    va_list vargs;

    if (callable == NULL || name == NULL)
        return null_error();

    callable = _PyObject_GetAttrId(callable, name);
    if (callable == NULL)
        return NULL;


    va_start(vargs, name);
    args = objargs_mktuple(vargs);
    va_end(vargs);
    if (args == NULL) {
        Py_DECREF(callable);
        return NULL;
    }
    tmp = PyObject_Call(callable, args, NULL);
    Py_DECREF(args);
    Py_DECREF(callable);

    return tmp;
}
