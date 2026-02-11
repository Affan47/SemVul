__Pyx_GetBuffer(PyObject *obj, Py_buffer *view, int flags) {
    CYTHON_UNUSED PyObject *getbuffer_cobj;
  #if PY_VERSION_HEX >= 0x02060000
    if (PyObject_CheckBuffer(obj)) return PyObject_GetBuffer(obj, view, flags);
  #endif
        if (PyObject_TypeCheck(obj, __pyx_ptype_5numpy_ndarray)) return __pyx_pw_5numpy_7ndarray_1__getbuffer__(obj, view, flags);
  #if PY_VERSION_HEX < 0x02060000
    if (obj->ob_type->tp_dict &&
        (getbuffer_cobj = PyMapping_GetItemString(obj->ob_type->tp_dict,
                                             "__pyx_getbuffer"))) {
        getbufferproc func;
      #if PY_VERSION_HEX >= 0x02070000 && !(PY_MAJOR_VERSION == 3 && PY_MINOR_VERSION == 0)
        func = (getbufferproc) PyCapsule_GetPointer(getbuffer_cobj, "getbuffer(obj, view, flags)");
      #else
        func = (getbufferproc) PyCObject_AsVoidPtr(getbuffer_cobj);
      #endif
        Py_DECREF(getbuffer_cobj);
        if (!func)
            goto fail;
        return func(obj, view, flags);
    } else {
        PyErr_Clear();
    }
  #endif
    PyErr_Format(PyExc_TypeError, "'%100s' does not have the buffer interface", Py_TYPE(obj)->tp_name);
#if PY_VERSION_HEX < 0x02060000
fail:
#endif
    return -1;
}
