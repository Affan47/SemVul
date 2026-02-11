stat_filemode(PyObject *self, PyObject *omode)
{
    char buf[10];
    mode_t mode;

    mode = _PyLong_AsMode_t(omode);
    if ((mode == (mode_t)-1) && PyErr_Occurred())
        return NULL;

    buf[0] = filetype(mode);
    fileperm(mode, &buf[1]);
    return PyUnicode_FromStringAndSize(buf, 10);
}
