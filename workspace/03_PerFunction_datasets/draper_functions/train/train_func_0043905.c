__pyx_tp_clear_6Cython_8Compiler_7Visitor_EnvTransform(PyObject *o) {
  PyObject* tmp;
  struct __pyx_obj_6Cython_8Compiler_7Visitor_EnvTransform *p = (struct __pyx_obj_6Cython_8Compiler_7Visitor_EnvTransform *)o;
  __pyx_tp_clear_6Cython_8Compiler_7Visitor_CythonTransform(o);
  tmp = ((PyObject*)p->env_stack);
  p->env_stack = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  return 0;
}
