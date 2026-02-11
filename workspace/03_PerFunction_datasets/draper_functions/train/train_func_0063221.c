__pyx_f_7dumbnet_ip_cksum_carry(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  int __pyx_v_sum;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  static char *__pyx_argnames[] = {"sum",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "i", __pyx_argnames, &__pyx_v_sum)) return 0;
  __pyx_1 = PyInt_FromLong(ip_cksum_carry(__pyx_v_sum)); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 318; goto __pyx_L1;}
  __pyx_r = __pyx_1;
  __pyx_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  __Pyx_AddTraceback("dumbnet.ip_cksum_carry");
  __pyx_r = 0;
  __pyx_L0:;
  return __pyx_r;
}
