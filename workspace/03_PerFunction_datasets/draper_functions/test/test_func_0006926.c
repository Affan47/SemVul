PyCFuncPtr_FromDll(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    char *name;
    int (* address)(void);
    PyObject *dll;
    PyObject *obj;
    PyCFuncPtrObject *self;
    void *handle;
    PyObject *paramflags = NULL;

    if (!PyArg_ParseTuple(args, "(O&O)|O", _get_name, &name, &dll, &paramflags))
        return NULL;
    if (paramflags == Py_None)
        paramflags = NULL;

    obj = PyObject_GetAttrString(dll, "_handle");
    if (!obj)
        return NULL;
    if (!PyLong_Check(obj)) {
        PyErr_SetString(PyExc_TypeError,
                        "the _handle attribute of the second argument must be an integer");
        Py_DECREF(obj);
        return NULL;
    }
    handle = (void *)PyLong_AsVoidPtr(obj);
    Py_DECREF(obj);
    if (PyErr_Occurred()) {
        PyErr_SetString(PyExc_ValueError,
                        "could not convert the _handle attribute to a pointer");
        return NULL;
    }

#ifdef MS_WIN32
    address = FindAddress(handle, name, (PyObject *)type);
    if (!address) {
        if (!IS_INTRESOURCE(name))
            PyErr_Format(PyExc_AttributeError,
                         "function '%s' not found",
                         name);
        else
            PyErr_Format(PyExc_AttributeError,
                         "function ordinal %d not found",
                         (WORD)(size_t)name);
        return NULL;
    }
#else
    address = (PPROC)ctypes_dlsym(handle, name);
    if (!address) {
#ifdef __CYGWIN__

        PyErr_Format(PyExc_AttributeError,
                     "function '%s' not found (%s) ",
                     name);
#else
        PyErr_SetString(PyExc_AttributeError, ctypes_dlerror());
#endif
        return NULL;
    }
#endif
    if (!_validate_paramflags(type, paramflags))
        return NULL;

    self = (PyCFuncPtrObject *)GenericPyCData_new(type, args, kwds);
    if (!self)
        return NULL;

    Py_XINCREF(paramflags);
    self->paramflags = paramflags;

    *(void **)self->b_ptr = address;

    Py_INCREF((PyObject *)dll);
    if (-1 == KeepRef((CDataObject *)self, 0, dll)) {
        Py_DECREF((PyObject *)self);
        return NULL;
    }

    Py_INCREF(self);
    self->callable = (PyObject *)self;
    return (PyObject *)self;
}
