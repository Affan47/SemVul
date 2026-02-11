CDataType_in_dll(PyObject *type, PyObject *args)
{
    PyObject *dll;
    char *name;
    PyObject *obj;
    void *handle;
    void *address;

    if (!PyArg_ParseTuple(args, "Os:in_dll", &dll, &name))
        return NULL;

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
    address = (void *)GetProcAddress(handle, name);
    if (!address) {
        PyErr_Format(PyExc_ValueError,
                     "symbol '%s' not found",
                     name);
        return NULL;
    }
#else
    address = (void *)ctypes_dlsym(handle, name);
    if (!address) {
#ifdef __CYGWIN__

        PyErr_Format(PyExc_ValueError,
                     "symbol '%s' not found (%s) ",
                     name);
#else
        PyErr_SetString(PyExc_ValueError, ctypes_dlerror());
#endif
        return NULL;
    }
#endif
    return PyCData_AtAddress(type, address);
}
