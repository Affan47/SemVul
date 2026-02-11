get_file(char *pathname, PyObject *fob, char *mode)
{
    FILE *fp;
    if (fob == NULL) {
        if (mode[0] == 'U')
            mode = "r" PY_STDIOTEXTMODE;
        fp = fopen(pathname, mode);
        if (fp == NULL)
            PyErr_SetFromErrno(PyExc_IOError);
    }
    else {
        fp = PyFile_AsFile(fob);
        if (fp == NULL)
            PyErr_SetString(PyExc_ValueError,
                            "bad/closed file object");
    }
    return fp;
}
