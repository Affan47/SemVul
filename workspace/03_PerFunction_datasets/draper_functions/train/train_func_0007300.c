weakref_richcompare(PyWeakReference* self, PyWeakReference* other, int op)
{
    if ((op != Py_EQ && op != Py_NE) ||
        !PyWeakref_Check(self) ||
        !PyWeakref_Check(other)) {
        Py_RETURN_NOTIMPLEMENTED;
    }
    if (PyWeakref_GET_OBJECT(self) == Py_None
        || PyWeakref_GET_OBJECT(other) == Py_None) {
        PyObject *res = self==other ? Py_True : Py_False;
        Py_INCREF(res);
        return res;
    }
    return PyObject_RichCompare(PyWeakref_GET_OBJECT(self),
                                PyWeakref_GET_OBJECT(other), op);
}
