_compile(PyObject* self_, PyObject* args)
{


    PatternObject* self;
    Py_ssize_t i, n;

    PyObject* pattern;
    int flags = 0;
    PyObject* code;
    Py_ssize_t groups = 0;
    PyObject* groupindex = NULL;
    PyObject* indexgroup = NULL;

    if (!PyArg_ParseTuple(args, "OiO!|nOO", &pattern, &flags,
                          &PyList_Type, &code, &groups,
                          &groupindex, &indexgroup))
        return NULL;

    n = PyList_GET_SIZE(code);

    self = PyObject_NEW_VAR(PatternObject, &Pattern_Type, n);
    if (!self)
        return NULL;
    self->weakreflist = NULL;
    self->pattern = NULL;
    self->groupindex = NULL;
    self->indexgroup = NULL;
    self->view.buf = NULL;

    self->codesize = n;

    for (i = 0; i < n; i++) {
        PyObject *o = PyList_GET_ITEM(code, i);
        unsigned long value = PyLong_AsUnsignedLong(o);
        self->code[i] = (SRE_CODE) value;
        if ((unsigned long) self->code[i] != value) {
            PyErr_SetString(PyExc_OverflowError,
                            "regular expression code size limit exceeded");
            break;
        }
    }

    if (PyErr_Occurred()) {
        Py_DECREF(self);
        return NULL;
    }

    if (pattern == Py_None) {
        self->logical_charsize = -1;
        self->charsize = -1;
    }
    else {
        Py_ssize_t p_length;
        if (!getstring(pattern, &p_length, &self->logical_charsize,
                       &self->charsize, &self->view)) {
            Py_DECREF(self);
            return NULL;
        }
    }

    Py_INCREF(pattern);
    self->pattern = pattern;

    self->flags = flags;

    self->groups = groups;

    Py_XINCREF(groupindex);
    self->groupindex = groupindex;

    Py_XINCREF(indexgroup);
    self->indexgroup = indexgroup;

    self->weakreflist = NULL;

    if (!_validate(self)) {
        Py_DECREF(self);
        return NULL;
    }

    return (PyObject*) self;
}
