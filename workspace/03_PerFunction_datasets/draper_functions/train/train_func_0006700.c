__pyx_pf_9lightning_4impl_12dataset_fast_7Dataset_get_n_samples(struct __pyx_obj_9lightning_4impl_12dataset_fast_Dataset *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("get_n_samples", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_PyInt_From_int(((struct __pyx_vtabstruct_9lightning_4impl_12dataset_fast_Dataset *)__pyx_v_self->__pyx_vtab)->get_n_samples(__pyx_v_self, 1)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 19; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;


  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("lightning.impl.dataset_fast.Dataset.get_n_samples", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
