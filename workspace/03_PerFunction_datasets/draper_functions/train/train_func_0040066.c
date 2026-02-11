__pyx_pf_7sklearn_4tree_5_tree_4Tree_5value___get__(struct __pyx_obj_7sklearn_4tree_5_tree_Tree *__pyx_v_self) {
  npy_intp __pyx_v_shape[3];
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);


  (__pyx_v_shape[0]) = ((npy_intp)__pyx_v_self->node_count);


  (__pyx_v_shape[1]) = ((npy_intp)__pyx_v_self->n_outputs);


  (__pyx_v_shape[2]) = ((npy_intp)__pyx_v_self->max_n_classes);


  __Pyx_XDECREF(__pyx_r);


  __pyx_t_1 = PyArray_SimpleNewFromData(3, __pyx_v_shape, NPY_DOUBLE, __pyx_v_self->value); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 187; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("sklearn.tree._tree.Tree.value.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
