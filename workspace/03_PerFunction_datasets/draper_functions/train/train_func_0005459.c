complex_format(PyComplexObject *v, int precision, char format_code)
{
    PyObject *result = NULL;
    Py_ssize_t len;


    char *pre = NULL;
    char *im = NULL;
    char *buf = NULL;


    char *re = NULL;
    char *lead = "";
    char *tail = "";

    if (v->cval.real == 0. && copysign(1.0, v->cval.real)==1.0) {
        re = "";
        im = PyOS_double_to_string(v->cval.imag, format_code,
                                   precision, 0, NULL);
        if (!im) {
            PyErr_NoMemory();
            goto done;
        }
    } else {

        pre = PyOS_double_to_string(v->cval.real, format_code,
                                    precision, 0, NULL);
        if (!pre) {
            PyErr_NoMemory();
            goto done;
        }
        re = pre;

        im = PyOS_double_to_string(v->cval.imag, format_code,
                                   precision, Py_DTSF_SIGN, NULL);
        if (!im) {
            PyErr_NoMemory();
            goto done;
        }
        lead = "(";
        tail = ")";
    }


    len = strlen(lead) + strlen(re) + strlen(im) + strlen(tail) + 2;
    buf = PyMem_Malloc(len);
    if (!buf) {
        PyErr_NoMemory();
        goto done;
    }
    PyOS_snprintf(buf, len, "%s%s%sj%s", lead, re, im, tail);
    result = PyString_FromString(buf);
  done:
    PyMem_Free(im);
    PyMem_Free(pre);
    PyMem_Free(buf);

    return result;
}
