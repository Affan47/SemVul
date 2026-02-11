string_concatenate(PyObject *v, PyObject *w,
                   PyFrameObject *f, unsigned char *next_instr)
{


    Py_ssize_t v_len = PyString_GET_SIZE(v);
    Py_ssize_t w_len = PyString_GET_SIZE(w);
    Py_ssize_t new_len = v_len + w_len;
    if (new_len < 0) {
        PyErr_SetString(PyExc_OverflowError,
                        "strings are too large to concat");
        return NULL;
    }

    if (v->ob_refcnt == 2) {


        switch (*next_instr) {
        case STORE_FAST:
        {
            int oparg = PEEKARG();
            PyObject **fastlocals = f->f_localsplus;
            if (GETLOCAL(oparg) == v)
                SETLOCAL(oparg, NULL);
            break;
        }
        case STORE_DEREF:
        {
            PyObject **freevars = (f->f_localsplus +
                                   f->f_code->co_nlocals);
            PyObject *c = freevars[PEEKARG()];
            if (PyCell_GET(c) == v)
                PyCell_Set(c, NULL);
            break;
        }
        case STORE_NAME:
        {
            PyObject *names = f->f_code->co_names;
            PyObject *name = GETITEM(names, PEEKARG());
            PyObject *locals = f->f_locals;
            if (PyDict_CheckExact(locals) &&
                PyDict_GetItem(locals, name) == v) {
                if (PyDict_DelItem(locals, name) != 0) {
                    PyErr_Clear();
                }
            }
            break;
        }
        }
    }

    if (v->ob_refcnt == 1 && !PyString_CHECK_INTERNED(v)) {


        if (_PyString_Resize(&v, new_len) != 0) {


            return NULL;
        }

        memcpy(PyString_AS_STRING(v) + v_len,
               PyString_AS_STRING(w), w_len);
        return v;
    }
    else {

        PyString_Concat(&v, w);
        return v;
    }
}
