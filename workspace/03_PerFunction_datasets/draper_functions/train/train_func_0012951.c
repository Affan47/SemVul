PyCursesWindow_GetCh(PyCursesWindowObject *self, PyObject *args)
{
    int x, y;
    int rtn;

    switch (PyTuple_Size(args)) {
    case 0:
        Py_BEGIN_ALLOW_THREADS
        rtn = wgetch(self->win);
        Py_END_ALLOW_THREADS
        break;
    case 2:
        if (!PyArg_ParseTuple(args,"ii;y,x",&y,&x))
            return NULL;
        Py_BEGIN_ALLOW_THREADS
        rtn = mvwgetch(self->win,y,x);
        Py_END_ALLOW_THREADS
        break;
    default:
        PyErr_SetString(PyExc_TypeError, "getch requires 0 or 2 arguments");
        return NULL;
    }
    return PyLong_FromLong((long)rtn);
}
