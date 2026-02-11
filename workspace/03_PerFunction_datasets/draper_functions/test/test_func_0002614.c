__pyx_f_6Cython_8Compiler_8Scanning_16CompileTimeScope_lookup_here(struct __pyx_obj_6Cython_8Compiler_8Scanning_CompileTimeScope *__pyx_v_self, PyObject *__pyx_v_name) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("lookup_here", 0);


  __Pyx_XDECREF(__pyx_r);
  if (unlikely(__pyx_v_self->entries == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 74; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = __Pyx_PyDict_GetItem(__pyx_v_self->entries, __pyx_v_name); if (unlikely(__pyx_t_1 == NULL)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 74; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;


  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("Cython.Compiler.Scanning.CompileTimeScope.lookup_here", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
