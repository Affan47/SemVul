__pyx_tp_traverse_6Cython_8Compiler_7Visitor_ScopeTrackingTransform(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_6Cython_8Compiler_7Visitor_ScopeTrackingTransform *p = (struct __pyx_obj_6Cython_8Compiler_7Visitor_ScopeTrackingTransform *)o;
  e = __pyx_tp_traverse_6Cython_8Compiler_7Visitor_CythonTransform(o, v, a); if (e) return e;
  if (p->scope_type) {
    e = (*v)(p->scope_type, a); if (e) return e;
  }
  if (p->scope_node) {
    e = (*v)(p->scope_node, a); if (e) return e;
  }
  return 0;
}
