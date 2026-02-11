__pyx_pw_13pybloomfilter_11BloomFilter_17copy_template(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_filename = 0;
  PyObject *__pyx_v_perm = 0;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("copy_template (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_filename,&__pyx_n_s_perm,0};
    PyObject* values[2] = {0,0};
    values[1] = ((PyObject *)__pyx_int_493);
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
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_filename)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s_perm);
          if (value) { values[1] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "copy_template") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 214; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_filename = values[0];
    __pyx_v_perm = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("copy_template", 0, 1, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 214; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("pybloomfilter.BloomFilter.copy_template", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_13pybloomfilter_11BloomFilter_16copy_template(((struct __pyx_obj_13pybloomfilter_BloomFilter *)__pyx_v_self), __pyx_v_filename, __pyx_v_perm);


  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
