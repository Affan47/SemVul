__pyx_f_9lightning_4impl_9loss_fast_7Squared_lipschitz_constant(CYTHON_UNUSED struct __pyx_obj_9lightning_4impl_9loss_fast_Squared *__pyx_v_self, CYTHON_UNUSED struct __pyx_obj_9lightning_4impl_12dataset_fast_RowDataset *__pyx_v_X, CYTHON_UNUSED int __pyx_v_n_vectors, int __pyx_skip_dispatch) {
  double __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  double __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("lipschitz_constant", 0);

  if (unlikely(__pyx_skip_dispatch)) ;

  else if (unlikely(Py_TYPE(((PyObject *)__pyx_v_self))->tp_dictoffset != 0)) {
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v_self), __pyx_n_s_lipschitz_constant); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 88; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    if (!PyCFunction_Check(__pyx_t_1) || (PyCFunction_GET_FUNCTION(__pyx_t_1) != (PyCFunction)__pyx_pw_9lightning_4impl_9loss_fast_7Squared_5lipschitz_constant)) {
      __pyx_t_2 = __Pyx_PyInt_From_int(__pyx_v_n_vectors); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 88; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 88; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_INCREF(((PyObject *)__pyx_v_X));
      PyTuple_SET_ITEM(__pyx_t_3, 0, ((PyObject *)__pyx_v_X));
      __Pyx_GIVEREF(((PyObject *)__pyx_v_X));
      PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_2);
      __Pyx_GIVEREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_3, NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 88; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_4 = __pyx_PyFloat_AsDouble(__pyx_t_2); if (unlikely((__pyx_t_4 == (double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 88; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_r = __pyx_t_4;
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      goto __pyx_L0;
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  }


  __pyx_r = 1.0;
  goto __pyx_L0;


  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_WriteUnraisable("lightning.impl.loss_fast.Squared.lipschitz_constant", __pyx_clineno, __pyx_lineno, __pyx_filename, 0);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
