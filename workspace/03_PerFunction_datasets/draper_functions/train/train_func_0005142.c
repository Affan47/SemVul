__pyx_memoryview_get_strides_MemoryView_10memoryview_7strides___get__(struct __pyx_memoryview_obj *__pyx_v_self) {
  int __pyx_v_i;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_t_3;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);


  __pyx_t_1 = (__pyx_v_self->view.strides == NULL);
  if (__pyx_t_1) {


    __pyx_t_2 = PyObject_Call(__pyx_builtin_ValueError, ((PyObject *)__pyx_k_tuple_42), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 528; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_Raise(__pyx_t_2, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    {__pyx_filename = __pyx_f[2]; __pyx_lineno = 528; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    goto __pyx_L3;
  }
  __pyx_L3:;


  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 530; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __pyx_v_self->view.ndim;
  for (__pyx_t_4 = 0; __pyx_t_4 < __pyx_t_3; __pyx_t_4+=1) {
    __pyx_v_i = __pyx_t_4;
    __pyx_t_5 = PyInt_FromSsize_t((__pyx_v_self->view.strides[__pyx_v_i])); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 530; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    if (unlikely(__Pyx_PyList_Append(__pyx_t_2, (PyObject*)__pyx_t_5))) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 530; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  }
  __pyx_t_5 = ((PyObject *)PyList_AsTuple(__pyx_t_2)); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 530; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_5));
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  __pyx_r = ((PyObject *)__pyx_t_5);
  __pyx_t_5 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("View.MemoryView.memoryview.strides.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
