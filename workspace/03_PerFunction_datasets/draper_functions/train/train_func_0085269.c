__pyx_f_7dumbnet___iter_append(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_entry = 0;
  PyObject *__pyx_v_l = 0;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  static char *__pyx_argnames[] = {"entry","l",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "OO", __pyx_argnames, &__pyx_v_entry, &__pyx_v_l)) return 0;
  Py_INCREF(__pyx_v_entry);
  Py_INCREF(__pyx_v_l);
  __pyx_1 = PyObject_GetAttr(__pyx_v_l, __pyx_n_append); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
  __pyx_2 = PyTuple_New(1); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
  Py_INCREF(__pyx_v_entry);
  PyTuple_SET_ITEM(__pyx_2, 0, __pyx_v_entry);
  __pyx_3 = PyObject_CallObject(__pyx_1, __pyx_2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_3); __pyx_3 = 0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("dumbnet.__iter_append");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_entry);
  Py_DECREF(__pyx_v_l);
  return __pyx_r;
}
