__pyx_pw_9lightning_4impl_12dataset_fast_1get_dataset(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_X = 0;
  PyObject *__pyx_v_order = 0;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("get_dataset (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_X,&__pyx_n_s_order,0};
    PyObject* values[2] = {0,0};
    values[1] = ((PyObject *)__pyx_n_s_c);
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_X)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s_order);
          if (value) { values[1] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "get_dataset") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 196; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_X = values[0];
    __pyx_v_order = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("get_dataset", 0, 1, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 196; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lightning.impl.dataset_fast.get_dataset", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_9lightning_4impl_12dataset_fast_get_dataset(__pyx_self, __pyx_v_X, __pyx_v_order);


  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
