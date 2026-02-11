__pyx_pf_6Cython_8Compiler_8Scanning_12PyrexScanner_14parse_comments___get__(struct __pyx_obj_6Cython_8Compiler_8Scanning_PyrexScanner *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_PyBool_FromLong(__pyx_v_self->parse_comments); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 29; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;


  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("Cython.Compiler.Scanning.PyrexScanner.parse_comments.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
