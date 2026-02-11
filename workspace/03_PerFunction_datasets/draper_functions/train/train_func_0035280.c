__pyx_f_6Cython_4Plex_7Actions_5Begin_perform(struct __pyx_obj_6Cython_4Plex_7Actions_Begin *__pyx_v_self, PyObject *__pyx_v_token_stream, CYTHON_UNUSED PyObject *__pyx_v_text) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("perform", 0);


  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_token_stream, __pyx_n_s_begin); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 66; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 66; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_self->state_name);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_self->state_name);
  __Pyx_GIVEREF(__pyx_v_self->state_name);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 66; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;


  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("Cython.Plex.Actions.Begin.perform", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
