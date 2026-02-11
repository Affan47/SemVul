class_setattr(PyClassObject *op, PyObject *name, PyObject *v)
{
    char *sname;
    if (PyEval_GetRestricted()) {
        PyErr_SetString(PyExc_RuntimeError,
                   "classes are read-only in restricted mode");
        return -1;
    }
    if (!PyString_Check(name)) {
        PyErr_SetString(PyExc_TypeError, "attribute name must be a string");
        return -1;
    }
    sname = PyString_AsString(name);
    if (sname[0] == '_' && sname[1] == '_') {
        Py_ssize_t n = PyString_Size(name);
        if (sname[n-1] == '_' && sname[n-2] == '_') {
            char *err = NULL;
            if (strcmp(sname, "__dict__") == 0)
                err = set_dict(op, v);
            else if (strcmp(sname, "__bases__") == 0)
                err = set_bases(op, v);
            else if (strcmp(sname, "__name__") == 0)
                err = set_name(op, v);
            else if (strcmp(sname, "__getattr__") == 0)
                set_slot(&op->cl_getattr, v);
            else if (strcmp(sname, "__setattr__") == 0)
                set_slot(&op->cl_setattr, v);
            else if (strcmp(sname, "__delattr__") == 0)
                set_slot(&op->cl_delattr, v);


            if (err != NULL) {
                if (*err == '\0')
                    return 0;
                PyErr_SetString(PyExc_TypeError, err);
                return -1;
            }
        }
    }
    if (v == NULL) {
        int rv = PyDict_DelItem(op->cl_dict, name);
        if (rv < 0)
            PyErr_Format(PyExc_AttributeError,
                         "class %.50s has no attribute '%.400s'",
                         PyString_AS_STRING(op->cl_name), sname);
        return rv;
    }
    else
        return PyDict_SetItem(op->cl_dict, name, v);
}
