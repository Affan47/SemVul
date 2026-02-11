wrapType(PyTypeObject *type, const jobject& obj)
{
    static PyObject *wrapfn_ = PyString_FromString("wrapfn_");
    PyObject *cobj = PyObject_GetAttr((PyObject *) type, wrapfn_);
    PyObject *(*wrapfn)(const jobject&);

    if (cobj == NULL)
        return NULL;

    wrapfn = (PyObject *(*)(const jobject &)) PyCObject_AsVoidPtr(cobj);
    Py_DECREF(cobj);

    return wrapfn(obj);
}
