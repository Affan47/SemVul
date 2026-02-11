__pyx_pf_7sklearn_12linear_model_8sgd_fast_18EpsilonInsensitive_6__reduce__(struct __pyx_obj_7sklearn_12linear_model_8sgd_fast_EpsilonInsensitive *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__reduce__", 0);


  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->epsilon); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 295; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 295; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 295; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(((PyObject *)((PyObject*)__pyx_ptype_7sklearn_12linear_model_8sgd_fast_EpsilonInsensitive)));
  PyTuple_SET_ITEM(__pyx_t_1, 0, ((PyObject *)((PyObject*)__pyx_ptype_7sklearn_12linear_model_8sgd_fast_EpsilonInsensitive)));
  __Pyx_GIVEREF(((PyObject *)((PyObject*)__pyx_ptype_7sklearn_12linear_model_8sgd_fast_EpsilonInsensitive)));
  PyTuple_SET_ITEM(__pyx_t_1, 1, ((PyObject *)__pyx_t_2));
  __Pyx_GIVEREF(((PyObject *)__pyx_t_2));
  __pyx_t_2 = 0;
  __pyx_r = ((PyObject *)__pyx_t_1);
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("sklearn.linear_model.sgd_fast.EpsilonInsensitive.__reduce__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
