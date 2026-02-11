__pyx_f_6Cython_8Compiler_8Scanning_12PyrexScanner_expect(struct __pyx_obj_6Cython_8Compiler_8Scanning_PyrexScanner *__pyx_v_self, PyObject *__pyx_v_what, struct __pyx_opt_args_6Cython_8Compiler_8Scanning_12PyrexScanner_expect *__pyx_optional_args) {
  PyObject *__pyx_v_message = ((PyObject *)Py_None);
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_t_2;
  struct __pyx_opt_args_6Cython_8Compiler_8Scanning_12PyrexScanner_expected __pyx_t_3;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("expect", 0);
  if (__pyx_optional_args) {
    if (__pyx_optional_args->__pyx_n > 0) {
      __pyx_v_message = __pyx_optional_args->message;
    }
  }


  __pyx_t_1 = PyObject_RichCompare(__pyx_v_self->sy, __pyx_v_what, Py_EQ); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 468; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_2 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_2 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 468; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (__pyx_t_2) {


    __pyx_t_1 = __pyx_f_6Cython_8Compiler_8Scanning_12PyrexScanner_next(__pyx_v_self); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 469; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    goto __pyx_L3;
  }
   {


    __pyx_t_3.__pyx_n = 1;
    __pyx_t_3.message = __pyx_v_message;
    __pyx_t_1 = __pyx_f_6Cython_8Compiler_8Scanning_12PyrexScanner_expected(__pyx_v_self, __pyx_v_what, &__pyx_t_3); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 471; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  }
  __pyx_L3:;


  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("Cython.Compiler.Scanning.PyrexScanner.expect", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -2;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
