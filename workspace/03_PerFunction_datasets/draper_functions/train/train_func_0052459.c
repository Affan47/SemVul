property_descr_set(PyObject *self, PyObject *obj, PyObject *value)
{
    propertyobject *gs = (propertyobject *)self;
    PyObject *func, *res;

    if (value == NULL)
        func = gs->prop_del;
    else
        func = gs->prop_set;
    if (func == NULL) {
        PyErr_SetString(PyExc_AttributeError,
                        value == NULL ?
                        "can't delete attribute" :
                "can't set attribute");
        return -1;
    }
    if (value == NULL)
        res = PyObject_CallFunction(func, "(O)", obj);
    else
        res = PyObject_CallFunction(func, "(OO)", obj, value);
    if (res == NULL)
        return -1;
    Py_DECREF(res);
    return 0;
}
