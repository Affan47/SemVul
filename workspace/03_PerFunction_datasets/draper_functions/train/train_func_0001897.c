type_set_name(PyTypeObject *type, PyObject *value, void *context)
{
    PyHeapTypeObject* et;
    char *tp_name;
    PyObject *tmp;

    if (!check_set_special_type_attr(type, value, "__name__"))
        return -1;
    if (!PyUnicode_Check(value)) {
        PyErr_Format(PyExc_TypeError,
                     "can only assign string to %s.__name__, not '%s'",
                     type->tp_name, Py_TYPE(value)->tp_name);
        return -1;
    }


    tmp = PyUnicode_FromStringAndSize("\0", 1);
    if (tmp == NULL)
        return -1;
    if (PyUnicode_Contains(value, tmp) != 0) {
        Py_DECREF(tmp);
        PyErr_Format(PyExc_ValueError,
                     "__name__ must not contain null bytes");
        return -1;
    }
    Py_DECREF(tmp);

    tp_name = _PyUnicode_AsString(value);
    if (tp_name == NULL)
        return -1;

    et = (PyHeapTypeObject*)type;

    Py_INCREF(value);


    tmp = et->ht_name;
    et->ht_name = value;

    type->tp_name = tp_name;
    Py_DECREF(tmp);

    return 0;
}
