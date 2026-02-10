__pyx_tp_clear_7sklearn_5utils_11seq_dataset_CSRDataset(PyObject *o) {
  struct __pyx_obj_7sklearn_5utils_11seq_dataset_CSRDataset *p = (struct __pyx_obj_7sklearn_5utils_11seq_dataset_CSRDataset *)o;
  PyObject* tmp;
  if (__pyx_ptype_7sklearn_5utils_11seq_dataset_SequentialDataset->tp_clear) {
    __pyx_ptype_7sklearn_5utils_11seq_dataset_SequentialDataset->tp_clear(o);
  }
  tmp = ((PyObject*)p->feature_indices);
  p->feature_indices = ((PyArrayObject *)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->index);
  p->index = ((PyArrayObject *)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  return 0;
}
