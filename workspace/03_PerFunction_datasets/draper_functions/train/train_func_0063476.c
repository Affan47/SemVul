read_object(RFILE *p)
{
    PyObject *v;
    if (PyErr_Occurred()) {
        fprintf(stderr, "XXX readobject called with exception set\n");
        return NULL;
    }
    v = r_object(p);
    if (v == NULL && !PyErr_Occurred())
        PyErr_SetString(PyExc_TypeError, "NULL object in marshal data for object");
    return v;
}
