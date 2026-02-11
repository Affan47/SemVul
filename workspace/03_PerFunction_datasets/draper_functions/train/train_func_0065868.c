__Pyx_PyList_Pop(PyObject* L) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX >= 0x02040000
    if (likely(PyList_GET_SIZE(L) > (((PyListObject*)L)->allocated >> 1))) {
        Py_SIZE(L) -= 1;
        return PyList_GET_ITEM(L, PyList_GET_SIZE(L));
    }
#endif
    return __Pyx_PyObject_CallMethod0(L, __pyx_n_s_pop);
}
