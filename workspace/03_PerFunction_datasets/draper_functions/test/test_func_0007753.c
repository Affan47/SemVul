__pyx_pf_9xmmsvalue_18CollectionOperands_8extend(PyObject *__pyx_v_self, PyObject *__pyx_v_ops) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("extend");
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = ((struct __pyx_vtabstruct_9xmmsvalue_CollectionOperands *)((struct __pyx_obj_9xmmsvalue_CollectionOperands *)__pyx_v_self)->__pyx_base.__pyx_vtab)->extend(((struct __pyx_obj_9xmmsvalue_CollectionOperands *)__pyx_v_self), __pyx_v_ops, 1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 582; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("xmmsvalue.CollectionOperands.extend", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
