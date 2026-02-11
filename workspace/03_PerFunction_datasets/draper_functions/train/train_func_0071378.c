encoder_clear(PyObject *self)
{

    PyEncoderObject *s;
    assert(PyEncoder_Check(self));
    s = (PyEncoderObject *)self;
    Py_CLEAR(s->markers);
    Py_CLEAR(s->defaultfn);
    Py_CLEAR(s->encoder);
    Py_CLEAR(s->indent);
    Py_CLEAR(s->key_separator);
    Py_CLEAR(s->item_separator);
    Py_CLEAR(s->sort_keys);
    Py_CLEAR(s->skipkeys);
    return 0;
}
