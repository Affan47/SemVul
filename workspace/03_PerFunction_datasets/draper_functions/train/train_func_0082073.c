__pyx_tp_new_7sklearn_5utils_13weight_vector_WeightVector(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_obj_7sklearn_5utils_13weight_vector_WeightVector *p;
  PyObject *o = (*t->tp_alloc)(t, 0);
  if (!o) return 0;
  p = ((struct __pyx_obj_7sklearn_5utils_13weight_vector_WeightVector *)o);
  p->__pyx_vtab = __pyx_vtabptr_7sklearn_5utils_13weight_vector_WeightVector;
  p->w = ((PyArrayObject *)Py_None); Py_INCREF(Py_None);
  if (__pyx_pf_7sklearn_5utils_13weight_vector_12WeightVector___cinit__(o, a, k) < 0) {
    Py_DECREF(o); o = 0;
  }
  return o;
}
