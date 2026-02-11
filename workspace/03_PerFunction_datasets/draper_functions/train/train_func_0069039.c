file_truncate(PyFileObject *f, PyObject *args)
{
    Py_off_t newsize;
    PyObject *newsizeobj = NULL;
    Py_off_t initialpos;
    int ret;

    if (f->f_fp == NULL)
        return err_closed();
    if (!f->writable)
        return err_mode("writing");
    if (!PyArg_UnpackTuple(args, "truncate", 0, 1, &newsizeobj))
        return NULL;


    FILE_BEGIN_ALLOW_THREADS(f)
    errno = 0;
    initialpos = _portable_ftell(f->f_fp);
    FILE_END_ALLOW_THREADS(f)
    if (initialpos == -1)
        goto onioerror;


    if (newsizeobj != NULL) {
#if !defined(HAVE_LARGEFILE_SUPPORT)
        newsize = PyInt_AsLong(newsizeobj);
#else
        newsize = PyLong_Check(newsizeobj) ?
                        PyLong_AsLongLong(newsizeobj) :
                PyInt_AsLong(newsizeobj);
#endif
        if (PyErr_Occurred())
            return NULL;
    }
    else
        newsize = initialpos;


    FILE_BEGIN_ALLOW_THREADS(f)
    errno = 0;
    ret = fflush(f->f_fp);
    FILE_END_ALLOW_THREADS(f)
    if (ret != 0)
        goto onioerror;

#ifdef MS_WINDOWS


    {
        HANDLE hFile;


        FILE_BEGIN_ALLOW_THREADS(f)
        errno = 0;
        ret = _portable_fseek(f->f_fp, newsize, SEEK_SET) != 0;
        FILE_END_ALLOW_THREADS(f)
        if (ret)
            goto onioerror;


        FILE_BEGIN_ALLOW_THREADS(f)
        errno = 0;
        hFile = (HANDLE)_get_osfhandle(fileno(f->f_fp));
        ret = hFile == (HANDLE)-1;
        if (ret == 0) {
            ret = SetEndOfFile(hFile) == 0;
            if (ret)
                errno = EACCES;
        }
        FILE_END_ALLOW_THREADS(f)
        if (ret)
            goto onioerror;
    }
#else
    FILE_BEGIN_ALLOW_THREADS(f)
    errno = 0;
    ret = ftruncate(fileno(f->f_fp), newsize);
    FILE_END_ALLOW_THREADS(f)
    if (ret != 0)
        goto onioerror;
#endif


    FILE_BEGIN_ALLOW_THREADS(f)
    errno = 0;
    ret = _portable_fseek(f->f_fp, initialpos, SEEK_SET) != 0;
    FILE_END_ALLOW_THREADS(f)
    if (ret)
        goto onioerror;

    Py_INCREF(Py_None);
    return Py_None;

onioerror:
    PyErr_SetFromErrno(PyExc_IOError);
    clearerr(f->f_fp);
    return NULL;
}
