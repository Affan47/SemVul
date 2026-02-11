PyFile_SetBufSize(PyObject *f, int bufsize)
{
    PyFileObject *file = (PyFileObject *)f;
    if (bufsize >= 0) {
        int type;
        switch (bufsize) {
        case 0:
            type = _IONBF;
            break;
#ifdef HAVE_SETVBUF
        case 1:
            type = _IOLBF;
            bufsize = BUFSIZ;
            break;
#endif
        default:
            type = _IOFBF;
#ifndef HAVE_SETVBUF
            bufsize = BUFSIZ;
#endif
            break;
        }
        fflush(file->f_fp);
        if (type == _IONBF) {
            PyMem_Free(file->f_setbuf);
            file->f_setbuf = NULL;
        } else {
            file->f_setbuf = (char *)PyMem_Realloc(file->f_setbuf,
                                                    bufsize);
        }
#ifdef HAVE_SETVBUF
        setvbuf(file->f_fp, file->f_setbuf, type, bufsize);
#else
        setbuf(file->f_fp, file->f_setbuf);
#endif
    }
}
