PyErr_SetFromErrnoWithFilenameObject(PyObject *exc, PyObject *filenameObject)
{
    PyObject *message;
    PyObject *v, *args;
    int i = errno;
#ifdef MS_WINDOWS
    WCHAR *s_buf = NULL;
#endif

#ifdef EINTR
    if (i == EINTR && PyErr_CheckSignals())
        return NULL;
#endif

#ifndef MS_WINDOWS
    if (i != 0) {
        char *s = strerror(i);
        message = PyUnicode_DecodeLocale(s, "surrogateescape");
    }
    else {

        message = PyUnicode_FromString("Error");
    }
#else
    if (i == 0)
        message = PyUnicode_FromString("Error");
    else
    {


        if (i > 0 && i < _sys_nerr) {
            message = PyUnicode_FromString(_sys_errlist[i]);
        }
        else {
            int len = FormatMessageW(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                i,
                MAKELANGID(LANG_NEUTRAL,
                           SUBLANG_DEFAULT),

                (LPWSTR) &s_buf,
                0,
                NULL);
            if (len==0) {


                s_buf = NULL;
                message = PyUnicode_FromFormat("Windows Error 0x%X", i);
            } else {

                while (len > 0 && (s_buf[len-1] <= L' ' || s_buf[len-1] == L'.'))
                    s_buf[--len] = L'\0';
                message = PyUnicode_FromWideChar(s_buf, len);
            }
        }
    }
#endif

    if (message == NULL)
    {
#ifdef MS_WINDOWS
        LocalFree(s_buf);
#endif
        return NULL;
    }

    if (filenameObject != NULL)
        args = Py_BuildValue("(iOO)", i, message, filenameObject);
    else
        args = Py_BuildValue("(iO)", i, message);
    Py_DECREF(message);

    if (args != NULL) {
        v = PyObject_Call(exc, args, NULL);
        Py_DECREF(args);
        if (v != NULL) {
            PyErr_SetObject((PyObject *) Py_TYPE(v), v);
            Py_DECREF(v);
        }
    }
#ifdef MS_WINDOWS
    LocalFree(s_buf);
#endif
    return NULL;
}
