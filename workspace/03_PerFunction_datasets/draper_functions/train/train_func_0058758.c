instance_int(PyInstanceObject *self)
{
    PyObject *truncated;
    static PyObject *int_name;
    if (int_name == NULL) {
        int_name = PyString_InternFromString("__int__");
        if (int_name == NULL)
            return NULL;
    }
    if (PyObject_HasAttr((PyObject*)self, int_name))
        return generic_unary_op(self, int_name);

    truncated = _instance_trunc(self);


    return _PyNumber_ConvertIntegralToInt(
        truncated,
        "__trunc__ returned non-Integral (type %.200s)");
}
