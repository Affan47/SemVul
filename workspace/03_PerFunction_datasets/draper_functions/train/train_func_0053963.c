PyFunction_New(PyObject *code, PyObject *globals)
{
    PyFunctionObject *op = PyObject_GC_New(PyFunctionObject,
                                        &PyFunction_Type);
    static PyObject *__name__ = 0;
    if (op != NULL) {
        PyObject *doc;
        PyObject *consts;
        PyObject *module;
        op->func_weakreflist = NULL;
        Py_INCREF(code);
        op->func_code = code;
        Py_INCREF(globals);
        op->func_globals = globals;
        op->func_name = ((PyCodeObject *)code)->co_name;
        Py_INCREF(op->func_name);
        op->func_defaults = NULL;
        op->func_closure = NULL;
        consts = ((PyCodeObject *)code)->co_consts;
        if (PyTuple_Size(consts) >= 1) {
            doc = PyTuple_GetItem(consts, 0);
            if (!PyString_Check(doc) && !PyUnicode_Check(doc))
                doc = Py_None;
        }
        else
            doc = Py_None;
        Py_INCREF(doc);
        op->func_doc = doc;
        op->func_dict = NULL;
        op->func_module = NULL;


        if (!__name__) {
            __name__ = PyString_InternFromString("__name__");
            if (!__name__) {
                Py_DECREF(op);
                return NULL;
            }
        }
        module = PyDict_GetItem(globals, __name__);
        if (module) {
            Py_INCREF(module);
            op->func_module = module;
        }
    }
    else
        return NULL;
    _PyObject_GC_TRACK(op);
    return (PyObject *)op;
}
