object_reduce_ex(PyObject *self, PyObject *args)
{
    PyObject *reduce, *res;
    int proto = 0;

    if (!PyArg_ParseTuple(args, "|i:__reduce_ex__", &proto))
        return NULL;

    reduce = PyObject_GetAttrString(self, "__reduce__");
    if (reduce == NULL)
        PyErr_Clear();
    else {
        PyObject *cls, *clsreduce, *objreduce;
        int override;
        cls = PyObject_GetAttrString(self, "__class__");
        if (cls == NULL) {
            Py_DECREF(reduce);
            return NULL;
        }
        clsreduce = PyObject_GetAttrString(cls, "__reduce__");
        Py_DECREF(cls);
        if (clsreduce == NULL) {
            Py_DECREF(reduce);
            return NULL;
        }
        objreduce = PyDict_GetItemString(PyBaseObject_Type.tp_dict,
                                         "__reduce__");
        override = (clsreduce != objreduce);
        Py_DECREF(clsreduce);
        if (override) {
            res = PyObject_CallObject(reduce, NULL);
            Py_DECREF(reduce);
            return res;
        }
        else
            Py_DECREF(reduce);
    }

    return _common_reduce(self, proto);
}
