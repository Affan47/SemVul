__pyx_pf_6Cython_8Compiler_7Visitor_16VisitorTransform_visitchildren(struct __pyx_obj_6Cython_8Compiler_7Visitor_VisitorTransform *__pyx_v_self, PyObject *__pyx_v_parent, PyObject *__pyx_v_attrs) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  struct __pyx_opt_args_6Cython_8Compiler_7Visitor_11TreeVisitor_visitchildren __pyx_t_2;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("visitchildren", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2.__pyx_n = 1;
  __pyx_t_2.attrs = __pyx_v_attrs;
  __pyx_t_1 = __pyx_vtabptr_6Cython_8Compiler_7Visitor_VisitorTransform->__pyx_base.visitchildren(((struct __pyx_obj_6Cython_8Compiler_7Visitor_TreeVisitor *)__pyx_v_self), __pyx_v_parent, 1, &__pyx_t_2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 240; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;


  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("Cython.Compiler.Visitor.VisitorTransform.visitchildren", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
