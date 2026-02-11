__pyx_f_7dumbnet_4addr_3eth___set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  int __pyx_3;
  unsigned short __pyx_4;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_value);


  __pyx_1 = PyInt_FromLong(PyString_Size(__pyx_v_value)); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 489; goto __pyx_L1;}
  __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_ETH_ADDR_LEN); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 489; goto __pyx_L1;}
  if (PyObject_Cmp(__pyx_1, __pyx_2, &__pyx_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 489; goto __pyx_L1;}
  __pyx_3 = __pyx_3 != 0;
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  if (__pyx_3) {
    __Pyx_Raise(PyExc_ValueError, __pyx_k16p, 0);
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 490; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;


  __pyx_1 = __pyx_f_7dumbnet___memcpy(((struct __pyx_obj_7dumbnet_addr *)__pyx_v_self)->_addr.addr_data8,__pyx_v_value,6); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 491; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;


  __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_ADDR_TYPE_ETH); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 492; goto __pyx_L1;}
  __pyx_4 = PyInt_AsLong(__pyx_2); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 492; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  ((struct __pyx_obj_7dumbnet_addr *)__pyx_v_self)->_addr.addr_type = __pyx_4;


  __pyx_1 = __Pyx_GetName(__pyx_m, __pyx_n_ETH_ADDR_BITS); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 493; goto __pyx_L1;}
  __pyx_4 = PyInt_AsLong(__pyx_1); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 493; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  ((struct __pyx_obj_7dumbnet_addr *)__pyx_v_self)->_addr.addr_bits = __pyx_4;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  __Pyx_AddTraceback("dumbnet.addr.eth.__set__");
  __pyx_r = -1;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_value);
  return __pyx_r;
}
