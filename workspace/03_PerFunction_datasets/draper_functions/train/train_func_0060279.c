init_ndbuf(PyObject *items, PyObject *shape, PyObject *strides,
           Py_ssize_t offset, PyObject *format, int flags)
{
    ndbuf_t *ndbuf;
    Py_ssize_t ndim;
    Py_ssize_t nitems;
    Py_ssize_t itemsize;


    CHECK_LIST_OR_TUPLE(shape)
    ndim = PySequence_Fast_GET_SIZE(shape);
    if (ndim > ND_MAX_NDIM) {
        PyErr_Format(PyExc_ValueError,
            "ndim must not exceed %d", ND_MAX_NDIM);
        return NULL;
    }


    if (strides) {
        CHECK_LIST_OR_TUPLE(strides)
        if (PySequence_Fast_GET_SIZE(strides) == 0)
            strides = NULL;
        else if (flags & ND_FORTRAN) {
            PyErr_SetString(PyExc_TypeError,
                "ND_FORTRAN cannot be used together with strides");
            return NULL;
        }
        else if (PySequence_Fast_GET_SIZE(strides) != ndim) {
            PyErr_SetString(PyExc_ValueError,
                "len(shape) != len(strides)");
            return NULL;
        }
    }


    itemsize = get_itemsize(format);
    if (itemsize <= 0) {
        if (itemsize == 0) {
            PyErr_SetString(PyExc_ValueError,
                "itemsize must not be zero");
        }
        return NULL;
    }


    if (ndim == 0) {
        items = Py_BuildValue("(O)", items);
        if (items == NULL)
            return NULL;
    }
    else {
        CHECK_LIST_OR_TUPLE(items)
        Py_INCREF(items);
    }


    nitems = PySequence_Fast_GET_SIZE(items);
    if (nitems == 0) {
        PyErr_SetString(PyExc_ValueError,
            "initializer list or tuple must not be empty");
        Py_DECREF(items);
        return NULL;
    }

    ndbuf = ndbuf_new(nitems, itemsize, offset, flags);
    if (ndbuf == NULL) {
        Py_DECREF(items);
        return NULL;
    }


    if (init_simple(ndbuf, items, format, itemsize) < 0)
        goto error;
    if (init_structure(ndbuf, shape, strides, ndim) < 0)
        goto error;

    Py_DECREF(items);
    return ndbuf;

error:
    Py_DECREF(items);
    ndbuf_free(ndbuf);
    return NULL;
}
