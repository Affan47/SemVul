__pyx_pf_6Cython_4Plex_7Actions_6Action_same_as(struct __pyx_obj_6Cython_4Plex_7Actions_Action *__pyx_v_self, PyObject *__pyx_v_other) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("same_as", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = ((struct __pyx_vtabstruct_6Cython_4Plex_7Actions_Action *)__pyx_v_self->__pyx_vtab)->same_as(__pyx_v_self, __pyx_v_other, 1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 14; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;


  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("Cython.Plex.Actions.Action.same_as", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
