codec_register(PyObject *self, PyObject *search_function)
{
    if (PyCodec_Register(search_function))
        return NULL;

    Py_RETURN_NONE;
}
