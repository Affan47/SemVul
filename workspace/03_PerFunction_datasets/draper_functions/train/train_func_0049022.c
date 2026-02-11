PyCursesWindow_GetKey(PyCursesWindowObject *self, PyObject *args)
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
        PyErr_SetString(PyExc_TypeError, "getkey requires 0 or 2 arguments");
        return NULL;
    }
    if (rtn == ERR) {

        PyErr_SetString(PyCursesError, "no input");
        return NULL;
    } else if (rtn<=255) {
        return Py_BuildValue("C", rtn);
    } else {
        const char *knp;
#if defined(__NetBSD__)
        knp = unctrl(rtn);
#else
        knp = keyname(rtn);
#endif
        return PyUnicode_FromString((knp == NULL) ? "" : knp);
    }
}
