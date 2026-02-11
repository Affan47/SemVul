pwd_getpwnam(PyObject *self, PyObject *args)
{
    char *name;
    struct passwd *p;
    if (!PyArg_ParseTuple(args, "s:getpwnam", &name))
        return NULL;
    if ((p = getpwnam(name)) == NULL) {
        PyErr_Format(PyExc_KeyError,
                     "getpwnam(): name not found: %s", name);
        return NULL;
    }
    return mkpwent(p);
}
