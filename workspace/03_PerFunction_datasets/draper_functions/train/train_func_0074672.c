textiowrapper_read_chunk(textio *self, Py_ssize_t size_hint)
{
    PyObject *dec_buffer = NULL;
    PyObject *dec_flags = NULL;
    PyObject *input_chunk = NULL;
    PyObject *decoded_chars, *chunk_size;
    Py_ssize_t nbytes, nchars;
    int eof;


    if (self->decoder == NULL) {
        _unsupported("not readable");
        return -1;
    }

    if (self->telling) {


        PyObject *state = PyObject_CallMethodObjArgs(self->decoder,
                                                     _PyIO_str_getstate, NULL);
        if (state == NULL)
            return -1;


        if (PyArg_Parse(state, "(OO)", &dec_buffer, &dec_flags) < 0) {
            Py_DECREF(state);
            return -1;
        }
        Py_INCREF(dec_buffer);
        Py_INCREF(dec_flags);
        Py_DECREF(state);
    }


    if (size_hint > 0) {
        size_hint = (Py_ssize_t)(Py_MAX(self->b2cratio, 1.0) * size_hint);
    }
    chunk_size = PyLong_FromSsize_t(Py_MAX(self->chunk_size, size_hint));
    if (chunk_size == NULL)
        goto fail;
    input_chunk = PyObject_CallMethodObjArgs(self->buffer,
        (self->has_read1 ? _PyIO_str_read1: _PyIO_str_read),
        chunk_size, NULL);
    Py_DECREF(chunk_size);
    if (input_chunk == NULL)
        goto fail;
    assert(PyBytes_Check(input_chunk));

    nbytes = PyBytes_Size(input_chunk);
    eof = (nbytes == 0);

    if (Py_TYPE(self->decoder) == &PyIncrementalNewlineDecoder_Type) {
        decoded_chars = _PyIncrementalNewlineDecoder_decode(
            self->decoder, input_chunk, eof);
    }
    else {
        decoded_chars = PyObject_CallMethodObjArgs(self->decoder,
            _PyIO_str_decode, input_chunk, eof ? Py_True : Py_False, NULL);
    }


    if (decoded_chars == NULL)
        goto fail;
    if (PyUnicode_READY(decoded_chars) == -1)
        goto fail;
    textiowrapper_set_decoded_chars(self, decoded_chars);
    nchars = PyUnicode_GET_LENGTH(decoded_chars);
    if (nchars > 0)
        self->b2cratio = (double) nbytes / nchars;
    else
        self->b2cratio = 0.0;
    if (nchars > 0)
        eof = 0;

    if (self->telling) {


        PyObject *next_input = PyNumber_Add(dec_buffer, input_chunk);
        if (next_input == NULL)
            goto fail;
        assert (PyBytes_Check(next_input));
        Py_DECREF(dec_buffer);
        Py_CLEAR(self->snapshot);
        self->snapshot = Py_BuildValue("NN", dec_flags, next_input);
    }
    Py_DECREF(input_chunk);

    return (eof == 0);

  fail:
    Py_XDECREF(dec_buffer);
    Py_XDECREF(dec_flags);
    Py_XDECREF(input_chunk);
    return -1;
}
