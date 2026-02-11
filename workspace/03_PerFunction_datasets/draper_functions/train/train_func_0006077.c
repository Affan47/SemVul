instance_pow(PyObject *v, PyObject *w, PyObject *z)
{
    if (z == Py_None) {
        return do_binop(v, w, "__pow__", "__rpow__", bin_power);
    }
    else {
        PyObject *func;
        PyObject *args;
        PyObject *result;


        func = PyObject_GetAttrString(v, "__pow__");
        if (func == NULL)
            return NULL;
        args = PyTuple_Pack(2, w, z);
        if (args == NULL) {
            Py_DECREF(func);
            return NULL;
        }
        result = PyEval_CallObject(func, args);
        Py_DECREF(func);
        Py_DECREF(args);
        return result;
    }
}
