float_print(PyFloatObject *v, FILE *fp, int flags)
{
    char *buf;
    if (flags & Py_PRINT_RAW)
        buf = PyOS_double_to_string(v->ob_fval,
                                    'g', PyFloat_STR_PRECISION,
                                    Py_DTSF_ADD_DOT_0, NULL);
    else
        buf = PyOS_double_to_string(v->ob_fval,
                            'r', 0, Py_DTSF_ADD_DOT_0, NULL);
    Py_BEGIN_ALLOW_THREADS
    fputs(buf, fp);
    Py_END_ALLOW_THREADS
    PyMem_Free(buf);
    return 0;
}
