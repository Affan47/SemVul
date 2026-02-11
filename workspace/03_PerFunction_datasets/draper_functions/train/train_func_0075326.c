posix_flistxattr(PyObject *self, PyObject *args)
{
    long fd;

    if (!PyArg_ParseTuple(args, "i:flistxattr", &fd))
        return NULL;
    return listxattr_common((const char *)(Py_uintptr_t)fd, wrap_flistxattr);
}
