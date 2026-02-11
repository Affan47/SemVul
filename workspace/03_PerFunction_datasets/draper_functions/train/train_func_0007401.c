open_device(PyObject *self, PyObject *args)
{
    char * uri;
    enum HPMUD_IO_MODE io_mode;
    HPMUD_DEVICE dd;
    enum HPMUD_RESULT result = HPMUD_R_OK;

    if (!PyArg_ParseTuple(args, "si", &uri, &io_mode))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    result = hpmud_open_device(uri, io_mode, &dd);
    Py_END_ALLOW_THREADS

    return Py_BuildValue("(ii)", result, dd);
}
