__pyx_pf_5numpy_7ndarray_2__releasebuffer__(PyArrayObject *__pyx_v_self, Py_buffer *__pyx_v_info) {
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("__releasebuffer__", 0);


  __pyx_t_1 = (PyArray_HASFIELDS(__pyx_v_self) != 0);
  if (__pyx_t_1) {


    free(__pyx_v_info->format);
    goto __pyx_L3;
  }
  __pyx_L3:;


  __pyx_t_1 = (((sizeof(npy_intp)) != (sizeof(Py_ssize_t))) != 0);
  if (__pyx_t_1) {


    free(__pyx_v_info->strides);
    goto __pyx_L4;
  }
  __pyx_L4:;


  __Pyx_RefNannyFinishContext();
}
