__Pyx_PyObject_Append(PyObject* L, PyObject* x) {
    if (likely(PyList_CheckExact(L))) {
        if (unlikely(PyList_Append(L, x) < 0)) return NULL;
        Py_INCREF(Py_None);
        return Py_None;
    } else {
        PyObject *r, *m;
        m = __Pyx_GetAttrString(L, "append");
        if (!m) return NULL;
        r = PyObject_CallFunctionObjArgs(m, x, NULL);
        Py_DECREF(m);
        return r;
    }
}
