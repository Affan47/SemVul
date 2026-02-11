OSError_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyOSErrorObject *self = NULL;
    PyObject *myerrno = NULL, *strerror = NULL, *filename = NULL;
#ifdef MS_WINDOWS
    PyObject *winerror = NULL;
#endif

    if (!oserror_use_init(type)) {
        if (!_PyArg_NoKeywords(type->tp_name, kwds))
            return NULL;

        Py_INCREF(args);
        if (oserror_parse_args(&args, &myerrno, &strerror, &filename
#ifdef MS_WINDOWS
                               , &winerror
#endif
            ))
            goto error;

        if (myerrno && PyLong_Check(myerrno) &&
            errnomap && (PyObject *) type == PyExc_OSError) {
            PyObject *newtype;
            newtype = PyDict_GetItem(errnomap, myerrno);
            if (newtype) {
                assert(PyType_Check(newtype));
                type = (PyTypeObject *) newtype;
            }
            else if (PyErr_Occurred())
                goto error;
        }
    }

    self = (PyOSErrorObject *) type->tp_alloc(type, 0);
    if (!self)
        goto error;

    self->dict = NULL;
    self->traceback = self->cause = self->context = NULL;
    self->written = -1;

    if (!oserror_use_init(type)) {
        if (oserror_init(self, &args, myerrno, strerror, filename
#ifdef MS_WINDOWS
                         , winerror
#endif
            ))
            goto error;
    }

    return (PyObject *) self;

error:
    Py_XDECREF(args);
    Py_XDECREF(self);
    return NULL;
}
