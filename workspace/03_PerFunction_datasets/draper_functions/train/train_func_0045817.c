__pyx_pf_7sklearn_8ensemble_18_gradient_boosting_4_partial_dependence_tree(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_7sklearn_4tree_5_tree_Tree *__pyx_v_tree, __Pyx_memviewslice __pyx_v_X, __Pyx_memviewslice __pyx_v_target_feature, double __pyx_v_learn_rate, __Pyx_memviewslice __pyx_v_out) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("_partial_dependence_tree", 0);
  __Pyx_XDECREF(__pyx_r);
  if (unlikely(!__pyx_v_X.memview)) { __Pyx_RaiseUnboundLocalError("X"); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 179; __pyx_clineno = __LINE__; goto __pyx_L1_error;} }
  if (unlikely(!__pyx_v_target_feature.memview)) { __Pyx_RaiseUnboundLocalError("target_feature"); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 179; __pyx_clineno = __LINE__; goto __pyx_L1_error;} }
  if (unlikely(!__pyx_v_out.memview)) { __Pyx_RaiseUnboundLocalError("out"); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 179; __pyx_clineno = __LINE__; goto __pyx_L1_error;} }
  __pyx_t_1 = __pyx_f_7sklearn_8ensemble_18_gradient_boosting__partial_dependence_tree(__pyx_v_tree, __pyx_v_X, __pyx_v_target_feature, __pyx_v_learn_rate, __pyx_v_out, 0); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 179; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("sklearn.ensemble._gradient_boosting._partial_dependence_tree", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __PYX_XDEC_MEMVIEW(&__pyx_v_X, 1);
  __PYX_XDEC_MEMVIEW(&__pyx_v_target_feature, 1);
  __PYX_XDEC_MEMVIEW(&__pyx_v_out, 1);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
