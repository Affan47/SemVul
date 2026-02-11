PyInt_FromUnicode(Py_UNICODE *s, Py_ssize_t length, int base)
{
    PyObject *result;
    char *buffer = (char *)PyMem_MALLOC(length+1);

    if (buffer == NULL)
        return PyErr_NoMemory();

    if (PyUnicode_EncodeDecimal(s, length, buffer, NULL)) {
        PyMem_FREE(buffer);
        return NULL;
    }
    result = PyInt_FromString(buffer, NULL, base);
    PyMem_FREE(buffer);
    return result;
}
