PyLocale_strxfrm(PyObject* self, PyObject* args)
{
    PyObject *str;
    Py_ssize_t n1;
    wchar_t *s = NULL, *buf = NULL;
    size_t n2;
    PyObject *result = NULL;

    if (!PyArg_ParseTuple(args, "U:strxfrm", &str))
        return NULL;

    s = PyUnicode_AsWideCharString(str, &n1);
    if (s == NULL)
        goto exit;


    n1 = n1 + 1;
    buf = PyMem_Malloc(n1 * sizeof(wchar_t));
    if (!buf) {
        PyErr_NoMemory();
        goto exit;
    }
    n2 = wcsxfrm(buf, s, n1);
    if (n2 >= (size_t)n1) {

        wchar_t * new_buf = PyMem_Realloc(buf, (n2+1)*sizeof(wchar_t));
        if (!new_buf) {
            PyErr_NoMemory();
            goto exit;
        }
        buf = new_buf;
        n2 = wcsxfrm(buf, s, n2+1);
    }
    result = PyUnicode_FromWideChar(buf, n2);
exit:
    if (buf)
        PyMem_Free(buf);
    if (s)
        PyMem_Free(s);
    return result;
}
