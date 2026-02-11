PyCursesWindow_NoOutRefresh(PyCursesWindowObject *self, PyObject *args)
{
    int pminrow,pmincol,sminrow,smincol,smaxrow,smaxcol;
    int rtn;

#ifndef WINDOW_HAS_FLAGS
    if (0)
#else
        if (self->win->_flags & _ISPAD)
#endif
        {
            switch(PyTuple_Size(args)) {
            case 6:
                if (!PyArg_ParseTuple(args,
                                      "iiiiii;" \
                                      "pminrow,pmincol,sminrow,smincol,smaxrow,smaxcol",
                                      &pminrow, &pmincol, &sminrow,
                                      &smincol, &smaxrow, &smaxcol))
                    return NULL;
                Py_BEGIN_ALLOW_THREADS
                rtn = pnoutrefresh(self->win,
                                   pminrow, pmincol, sminrow,
                                   smincol, smaxrow, smaxcol);
                Py_END_ALLOW_THREADS
                return PyCursesCheckERR(rtn, "pnoutrefresh");
            default:
                PyErr_SetString(PyCursesError,
                                "noutrefresh() called for a pad "
                                "requires 6 arguments");
                return NULL;
            }
        } else {
            if (!PyArg_ParseTuple(args, ":noutrefresh"))
                return NULL;

            Py_BEGIN_ALLOW_THREADS
            rtn = wnoutrefresh(self->win);
            Py_END_ALLOW_THREADS
            return PyCursesCheckERR(rtn, "wnoutrefresh");
        }
}
