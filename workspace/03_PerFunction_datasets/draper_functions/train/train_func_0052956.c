__pyx_f_7dumbnet_4addr_8addrtype___set__(PyObject *__pyx_v_self, PyObject *__pyx_arg_value) {
  unsigned int __pyx_v_value;
  int __pyx_r;
  int __pyx_1;
  Py_INCREF(__pyx_v_self);
  __pyx_v_value = PyInt_AsUnsignedLongMask(__pyx_arg_value); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 457; goto __pyx_L1;}


  __pyx_1 = (__pyx_v_value > 0xffff);
  if (__pyx_1) {
    __Pyx_Raise(PyExc_OverflowError, 0, 0);
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 458; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;


  ((struct __pyx_obj_7dumbnet_addr *)__pyx_v_self)->_addr.addr_type = __pyx_v_value;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("dumbnet.addr.addrtype.__set__");
  __pyx_r = -1;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}
