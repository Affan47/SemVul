newarrayobject(PyTypeObject *type, Py_ssize_t size, struct arraydescr *descr)
{
    arrayobject *op;
    size_t nbytes;

    if (size < 0) {
        PyErr_BadInternalCall();
        return NULL;
    }

    nbytes = size * descr->itemsize;

    if (nbytes / descr->itemsize != (size_t)size) {
        return PyErr_NoMemory();
    }
    op = (arrayobject *) type->tp_alloc(type, 0);
    if (op == NULL) {
        return NULL;
    }
    op->ob_descr = descr;
    op->allocated = size;
    op->weakreflist = NULL;
    Py_SIZE(op) = size;
    if (size <= 0) {
        op->ob_item = NULL;
    }
    else {
        op->ob_item = PyMem_NEW(char, nbytes);
        if (op->ob_item == NULL) {
            Py_DECREF(op);
            return PyErr_NoMemory();
        }
    }
    op->ob_exports = 0;
    return (PyObject *) op;
}
