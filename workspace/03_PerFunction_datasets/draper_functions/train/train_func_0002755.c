__pyx_f_4jdwp_10JdwpBuffer_unpackStr(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  uint32_t __pyx_v_sz;
  char *__pyx_v_str;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF(__pyx_v_self);


  __pyx_1 = __pyx_f_4jdwp_einz(jdwp_unpack_str((&((struct __pyx_obj_4jdwp_JdwpBuffer *)__pyx_v_self)->buf),(&__pyx_v_sz),(&__pyx_v_str))); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 166; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;


  __pyx_1 = PyString_FromStringAndSize(__pyx_v_str,__pyx_v_sz); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 167; goto __pyx_L1;}
  __pyx_r = __pyx_1;
  __pyx_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  __Pyx_AddTraceback("jdwp.JdwpBuffer.unpackStr");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}
