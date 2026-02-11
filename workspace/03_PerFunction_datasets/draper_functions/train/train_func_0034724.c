PyCurses_GetWin(PyCursesWindowObject *self, PyObject *stream)
{
    char fn[100];
    int fd;
    FILE *fp;
    PyObject *data;
    size_t datalen;
    WINDOW *win;

    PyCursesInitialised;
    _Py_IDENTIFIER(read);

    strcpy(fn, "/tmp/py.curses.getwin.XXXXXX");
    fd = mkstemp(fn);
    if (fd < 0)
        return PyErr_SetFromErrnoWithFilename(PyExc_IOError, fn);
    fp = fdopen(fd, "wb+");
    if (fp == NULL) {
        close(fd);
        remove(fn);
        return PyErr_SetFromErrnoWithFilename(PyExc_IOError, fn);
    }
    data = _PyObject_CallMethodId(stream, &PyId_read, "");
    if (data == NULL) {
        fclose(fp);
        remove(fn);
        return NULL;
    }
    if (!PyBytes_Check(data)) {
        PyErr_Format(PyExc_TypeError,
                     "f.read() returned %.100s instead of bytes",
                     data->ob_type->tp_name);
        Py_DECREF(data);
        fclose(fp);
        remove(fn);
        return NULL;
    }
    datalen = PyBytes_GET_SIZE(data);
    if (fwrite(PyBytes_AS_STRING(data), 1, datalen, fp) != datalen) {
        Py_DECREF(data);
        fclose(fp);
        remove(fn);
        return PyErr_SetFromErrnoWithFilename(PyExc_IOError, fn);
    }
    Py_DECREF(data);
    fseek(fp, 0, 0);
    win = getwin(fp);
    fclose(fp);
    remove(fn);
    if (win == NULL) {
        PyErr_SetString(PyCursesError, catchall_NULL);
        return NULL;
    }
    return PyCursesWindow_New(win, NULL);
}
