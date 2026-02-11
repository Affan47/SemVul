spwd_getspnam(PyObject *self, PyObject *args)
{
    char *name;
    struct spwd *p;
    PyObject *arg, *bytes, *retval = NULL;

    if (!PyArg_ParseTuple(args, "U:getspnam", &arg))
        return NULL;
    if ((bytes = PyUnicode_EncodeFSDefault(arg)) == NULL)
        return NULL;
    if (PyBytes_AsStringAndSize(bytes, &name, NULL) == -1)
        goto out;
    if ((p = getspnam(name)) == NULL) {
        PyErr_SetString(PyExc_KeyError, "getspnam(): name not found");
        goto out;
    }
    retval = mkspent(p);
out:
    Py_DECREF(bytes);
    return retval;
}
