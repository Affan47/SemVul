close_the_file(PyFileObject *f)
{
    int sts = 0;
    int (*local_close)(FILE *);
    FILE *local_fp = f->f_fp;
    char *local_setbuf = f->f_setbuf;
    if (local_fp != NULL) {
        local_close = f->f_close;
        if (local_close != NULL && f->unlocked_count > 0) {
            if (f->ob_refcnt > 0) {
                PyErr_SetString(PyExc_IOError,
                    "close() called during concurrent "
                    "operation on the same file object.");
            } else {


                PyErr_SetString(PyExc_SystemError,
                    "PyFileObject locking error in "
                    "destructor (refcnt <= 0 at close).");
            }
            return NULL;
        }


        f->f_fp = NULL;
        if (local_close != NULL) {


            f->f_setbuf = NULL;
            Py_BEGIN_ALLOW_THREADS
            errno = 0;
            sts = (*local_close)(local_fp);
            Py_END_ALLOW_THREADS
            f->f_setbuf = local_setbuf;
            if (sts == EOF)
                return PyErr_SetFromErrno(PyExc_IOError);
            if (sts != 0)
                return PyInt_FromLong((long)sts);
        }
    }
    Py_RETURN_NONE;
}
