mro_internal(PyTypeObject *type, PyObject **p_old_mro)
{
    PyObject *new_mro, *old_mro;
    int reent;


    old_mro = type->tp_mro;
    Py_XINCREF(old_mro);
    new_mro = mro_invoke(type);
    reent = (type->tp_mro != old_mro);
    Py_XDECREF(old_mro);
    if (new_mro == NULL)
        return -1;

    if (reent) {
        Py_DECREF(new_mro);
        return 0;
    }

    type->tp_mro = new_mro;

    type_mro_modified(type, type->tp_mro);


    type_mro_modified(type, type->tp_bases);

    PyType_Modified(type);

    if (p_old_mro != NULL)
        *p_old_mro = old_mro;
    else
        Py_XDECREF(old_mro);

    return 1;
}
