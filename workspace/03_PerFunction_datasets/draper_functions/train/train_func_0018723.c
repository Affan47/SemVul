close_device(PyObject *self, PyObject *args)
{
    HPMUD_DEVICE dd;
    enum HPMUD_RESULT result = HPMUD_R_OK;

    if (!PyArg_ParseTuple(args, "i", &dd))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    result = hpmud_close_device(dd);
    Py_END_ALLOW_THREADS

    return Py_BuildValue("i", result);
}
