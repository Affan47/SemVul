posix_setreuid (PyObject *self, PyObject *args)
{
    long ruid_arg, euid_arg;
    uid_t ruid, euid;
    if (!PyArg_ParseTuple(args, "ll", &ruid_arg, &euid_arg))
        return NULL;
    if (ruid_arg == -1)
        ruid = (uid_t)-1;
    else
        ruid = ruid_arg;
    if (euid_arg == -1)
        euid = (uid_t)-1;
    else
        euid = euid_arg;
    if ((euid_arg != -1 && euid != euid_arg) ||
        (ruid_arg != -1 && ruid != ruid_arg)) {
        PyErr_SetString(PyExc_OverflowError, "user id too big");
        return NULL;
    }
    if (setreuid(ruid, euid) < 0) {
        return posix_error();
    } else {
        Py_INCREF(Py_None);
        return Py_None;
    }
}
