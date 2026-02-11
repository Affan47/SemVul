__pyx_memoryview_get_shape_MemoryView_10memoryview_5shape___get__(struct __pyx_memoryview_obj *__pyx_v_self) {
  int __pyx_v_i;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_t_2;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);


  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyList_New(0); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 521; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __pyx_v_self->view.ndim;
  for (__pyx_t_3 = 0; __pyx_t_3 < __pyx_t_2; __pyx_t_3+=1) {
    __pyx_v_i = __pyx_t_3;
    __pyx_t_4 = PyInt_FromSsize_t((__pyx_v_self->view.shape[__pyx_v_i])); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 521; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    if (unlikely(__Pyx_PyList_Append(__pyx_t_1, (PyObject*)__pyx_t_4))) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 521; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  }
  __pyx_t_4 = ((PyObject *)PyList_AsTuple(__pyx_t_1)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 521; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_4));
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
  __pyx_r = ((PyObject *)__pyx_t_4);
  __pyx_t_4 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("View.MemoryView.memoryview.shape.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
