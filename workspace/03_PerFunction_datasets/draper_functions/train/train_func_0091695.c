frame_settrace(PyFrameObject *f, PyObject* v, void *closure)
{
    PyObject* old_value;


    f->f_lineno = PyFrame_GetLineNumber(f);

    old_value = f->f_trace;
    Py_XINCREF(v);
    f->f_trace = v;
    Py_XDECREF(old_value);

    return 0;
}
