PyObject_IsTrue(PyObject *v)
{
    Py_ssize_t res;
    if (v == Py_True)
        return 1;
    if (v == Py_False)
        return 0;
    if (v == Py_None)
        return 0;
    else if (v->ob_type->tp_as_number != NULL &&
             v->ob_type->tp_as_number->nb_bool != NULL)
        res = (*v->ob_type->tp_as_number->nb_bool)(v);
    else if (v->ob_type->tp_as_mapping != NULL &&
             v->ob_type->tp_as_mapping->mp_length != NULL)
        res = (*v->ob_type->tp_as_mapping->mp_length)(v);
    else if (v->ob_type->tp_as_sequence != NULL &&
             v->ob_type->tp_as_sequence->sq_length != NULL)
        res = (*v->ob_type->tp_as_sequence->sq_length)(v);
    else
        return 1;

    return (res > 0) ? 1 : Py_SAFE_DOWNCAST(res, Py_ssize_t, int);
}
