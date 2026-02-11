PyCurses_tparm(PyObject *self, PyObject *args)
{
    char* fmt;
    char* result = NULL;
    int i1=0,i2=0,i3=0,i4=0,i5=0,i6=0,i7=0,i8=0,i9=0;

    PyCursesSetupTermCalled;

    if (!PyArg_ParseTuple(args, "y|iiiiiiiii:tparm",
                          &fmt, &i1, &i2, &i3, &i4,
                          &i5, &i6, &i7, &i8, &i9)) {
        return NULL;
    }

    result = tparm(fmt,i1,i2,i3,i4,i5,i6,i7,i8,i9);
    if (!result) {
        PyErr_SetString(PyCursesError, "tparm() returned NULL");
        return NULL;
    }

    return PyBytes_FromString(result);
}
