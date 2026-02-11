_PyObject_GetAttrId(PyObject *v, _Py_Identifier *name)
{
    PyObject *result;
    PyObject *oname = _PyUnicode_FromId(name);
    if (!oname)
        return NULL;
    result = PyObject_GetAttr(v, oname);
    return result;
}
