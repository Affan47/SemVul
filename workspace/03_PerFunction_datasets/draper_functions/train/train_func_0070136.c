open_the_file(PyFileObject *f, char *name, char *mode)
{
    char *newmode;
    assert(f != NULL);
    assert(PyFile_Check(f));
#ifdef MS_WINDOWS

    assert(f->f_name != NULL);
#else
    assert(name != NULL);
#endif
    assert(mode != NULL);
    assert(f->f_fp == NULL);


    newmode = PyMem_MALLOC(strlen(mode) + 3);
    if (!newmode) {
        PyErr_NoMemory();
        return NULL;
    }
    strcpy(newmode, mode);

    if (_PyFile_SanitizeMode(newmode)) {
        f = NULL;
        goto cleanup;
    }


    if (PyEval_GetRestricted()) {
        PyErr_SetString(PyExc_IOError,
        "file() constructor not accessible in restricted mode");
        f = NULL;
        goto cleanup;
    }
    errno = 0;

#ifdef MS_WINDOWS
    if (PyUnicode_Check(f->f_name)) {
        PyObject *wmode;
        wmode = PyUnicode_DecodeASCII(newmode, strlen(newmode), NULL);
        if (f->f_name && wmode) {
            FILE_BEGIN_ALLOW_THREADS(f)


            f->f_fp = _wfopen(PyUnicode_AS_UNICODE(f->f_name),
                              PyUnicode_AS_UNICODE(wmode));
            FILE_END_ALLOW_THREADS(f)
        }
        Py_XDECREF(wmode);
    }
#endif
    if (NULL == f->f_fp && NULL != name) {
        FILE_BEGIN_ALLOW_THREADS(f)
        f->f_fp = fopen(name, newmode);
        FILE_END_ALLOW_THREADS(f)
    }

    if (f->f_fp == NULL) {
#if defined  _MSC_VER && (_MSC_VER < 1400 || !defined(__STDC_SECURE_LIB__))


        if (errno == 0)
            errno = EINVAL;
        else if (errno == EINVAL)
            errno = ENOENT;
#endif


        if (errno == EINVAL) {
            PyObject *v;
            char message[100];
            PyOS_snprintf(message, 100,
                "invalid mode ('%.50s') or filename", mode);
            v = Py_BuildValue("(isO)", errno, message, f->f_name);
            if (v != NULL) {
                PyErr_SetObject(PyExc_IOError, v);
                Py_DECREF(v);
            }
        }
        else
            PyErr_SetFromErrnoWithFilenameObject(PyExc_IOError, f->f_name);
        f = NULL;
    }
    if (f != NULL)
        f = dircheck(f);

cleanup:
    PyMem_FREE(newmode);

    return (PyObject *)f;
}
