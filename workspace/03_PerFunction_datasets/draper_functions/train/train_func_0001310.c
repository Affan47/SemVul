__pyx_tp_clear_6Cython_8Compiler_7Visitor_RecursiveNodeReplacer(PyObject *o) {
  PyObject* tmp;
  struct __pyx_obj_6Cython_8Compiler_7Visitor_RecursiveNodeReplacer *p = (struct __pyx_obj_6Cython_8Compiler_7Visitor_RecursiveNodeReplacer *)o;
  __pyx_tp_clear_6Cython_8Compiler_7Visitor_TreeVisitor(o);
  tmp = ((PyObject*)p->orig_node);
  p->orig_node = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->new_node);
  p->new_node = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  return 0;
}
