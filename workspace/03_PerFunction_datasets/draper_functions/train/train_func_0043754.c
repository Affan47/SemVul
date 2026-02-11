PySequence_SetItem(PyObject *s, Py_ssize_t i, PyObject *o)
{
    PySequenceMethods *m;

    if (s == NULL) {
        null_error();
        return -1;
    }

    m = s->ob_type->tp_as_sequence;
    if (m && m->sq_ass_item) {
        if (i < 0) {
            if (m->sq_length) {
                Py_ssize_t l = (*m->sq_length)(s);
                if (l < 0)
                    return -1;
                i += l;
            }
        }
        return m->sq_ass_item(s, i, o);
    }

    type_error("'%.200s' object does not support item assignment", s);
    return -1;
}
