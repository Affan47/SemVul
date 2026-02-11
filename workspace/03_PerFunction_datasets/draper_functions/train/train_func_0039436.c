unicode_internal_decode(PyObject *self,
                        PyObject *args)
{
    PyObject *obj;
    const char *errors = NULL;

    if (!PyArg_ParseTuple(args, "O|z:unicode_internal_decode",
                          &obj, &errors))
        return NULL;

    if (PyUnicode_Check(obj)) {
        if (PyUnicode_READY(obj) < 0)
            return NULL;
        Py_INCREF(obj);
        return codec_tuple(obj, PyUnicode_GET_LENGTH(obj));
    }
    else {
        Py_buffer view;
        PyObject *result;
        if (PyObject_GetBuffer(obj, &view, PyBUF_SIMPLE) != 0)
            return NULL;

        result = codec_tuple(
                _PyUnicode_DecodeUnicodeInternal(view.buf, view.len, errors),
                view.len);
        PyBuffer_Release(&view);
        return result;
    }
}
