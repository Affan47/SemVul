attrgetter_call(attrgetterobject *ag, PyObject *args, PyObject *kw)
{
    PyObject *obj, *result;
    Py_ssize_t i, nattrs=ag->nattrs;

    if (!PyArg_UnpackTuple(args, "attrgetter", 1, 1, &obj))
        return NULL;
    if (ag->nattrs == 1)
        return dotted_getattr(obj, ag->attr);

    assert(PyTuple_Check(ag->attr));
    assert(PyTuple_GET_SIZE(ag->attr) == nattrs);

    result = PyTuple_New(nattrs);
    if (result == NULL)
        return NULL;

    for (i=0 ; i < nattrs ; i++) {
        PyObject *attr, *val;
        attr = PyTuple_GET_ITEM(ag->attr, i);
        val = dotted_getattr(obj, attr);
        if (val == NULL) {
            Py_DECREF(result);
            return NULL;
        }
        PyTuple_SET_ITEM(result, i, val);
    }
    return result;
}
