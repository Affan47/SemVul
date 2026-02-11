range_item(rangeobject *r, Py_ssize_t i)
{
    if (i < 0 || i >= r->len) {
        PyErr_SetString(PyExc_IndexError,
                        "xrange object index out of range");
        return NULL;
    }


    return PyInt_FromLong((long)(r->start + (unsigned long)i * r->step));
}
