PyCData_set(PyObject *dst, PyObject *type, SETFUNC setfunc, PyObject *value,
          Py_ssize_t index, Py_ssize_t size, char *ptr)
{
    CDataObject *mem = (CDataObject *)dst;
    PyObject *result;

    if (!CDataObject_Check(dst)) {
        PyErr_SetString(PyExc_TypeError,
                        "not a ctype instance");
        return -1;
    }

    result = _PyCData_set(mem, type, setfunc, value,
                        size, ptr);
    if (result == NULL)
        return -1;


    return KeepRef(mem, index, result);
}
