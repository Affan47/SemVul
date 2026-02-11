__pyx_tp_dealloc_7sklearn_5utils_11seq_dataset_CSRDataset(PyObject *o) {
  struct __pyx_obj_7sklearn_5utils_11seq_dataset_CSRDataset *p = (struct __pyx_obj_7sklearn_5utils_11seq_dataset_CSRDataset *)o;
  PyObject_GC_UnTrack(o);
  Py_CLEAR(p->feature_indices);
  Py_CLEAR(p->index);
  PyObject_GC_Track(o);
  __pyx_tp_dealloc_7sklearn_5utils_11seq_dataset_SequentialDataset(o);
}
