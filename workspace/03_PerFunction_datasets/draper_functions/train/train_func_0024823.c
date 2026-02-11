kwd_as_string(PyObject *kwd) {
#ifdef Py_USING_UNICODE
    if (PyString_Check(kwd)) {
#else
        assert(PyString_Check(kwd));
#endif
        Py_INCREF(kwd);
        return kwd;
#ifdef Py_USING_UNICODE
    }
    return _PyUnicode_AsDefaultEncodedString(kwd, "replace");
#endif
}
