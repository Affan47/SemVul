__pyx_tp_traverse_6Cython_8Compiler_8Scanning_CompileTimeScope(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_6Cython_8Compiler_8Scanning_CompileTimeScope *p = (struct __pyx_obj_6Cython_8Compiler_8Scanning_CompileTimeScope *)o;
  if (p->entries) {
    e = (*v)(p->entries, a); if (e) return e;
  }
  if (p->outer) {
    e = (*v)(((PyObject*)p->outer), a); if (e) return e;
  }
  return 0;
}
