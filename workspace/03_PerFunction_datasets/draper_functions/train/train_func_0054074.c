PySequence_InPlaceConcat(PyObject *s, PyObject *o)
{
    PySequenceMethods *m;

    if (s == NULL || o == NULL)
        return null_error();

    m = s->ob_type->tp_as_sequence;
    if (m && HASINPLACE(s) && m->sq_inplace_concat)
        return m->sq_inplace_concat(s, o);
    if (m && m->sq_concat)
        return m->sq_concat(s, o);

    if (PySequence_Check(s) && PySequence_Check(o)) {
        PyObject *result = binary_iop1(s, o, NB_SLOT(nb_inplace_add),
                                       NB_SLOT(nb_add));
        if (result != Py_NotImplemented)
            return result;
        Py_DECREF(result);
    }
    return type_error("'%.200s' object can't be concatenated", s);
}
