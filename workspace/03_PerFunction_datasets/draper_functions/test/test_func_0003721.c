__pyx_pf_9xmmsvalue_12XmmsDictIter_1__dealloc__(PyObject *__pyx_v_self) {
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("__dealloc__");


  __pyx_t_1 = (((struct __pyx_obj_9xmmsvalue_XmmsDictIter *)__pyx_v_self)->it != NULL);
  if (__pyx_t_1) {


    xmmsv_dict_iter_explicit_destroy(((struct __pyx_obj_9xmmsvalue_XmmsDictIter *)__pyx_v_self)->it);
    goto __pyx_L5;
  }
  __pyx_L5:;


  __pyx_t_1 = (((struct __pyx_obj_9xmmsvalue_XmmsDictIter *)__pyx_v_self)->val != NULL);
  if (__pyx_t_1) {


    xmmsv_unref(((struct __pyx_obj_9xmmsvalue_XmmsDictIter *)__pyx_v_self)->val);
    goto __pyx_L6;
  }
  __pyx_L6:;

  __Pyx_RefNannyFinishContext();
}
