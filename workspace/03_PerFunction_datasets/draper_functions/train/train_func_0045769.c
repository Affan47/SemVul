__pyx_tp_clear_6Cython_4Plex_7Actions_Begin(PyObject *o) {
  PyObject* tmp;
  struct __pyx_obj_6Cython_4Plex_7Actions_Begin *p = (struct __pyx_obj_6Cython_4Plex_7Actions_Begin *)o;
  if (likely(__pyx_ptype_6Cython_4Plex_7Actions_Action)) { if (__pyx_ptype_6Cython_4Plex_7Actions_Action->tp_clear) __pyx_ptype_6Cython_4Plex_7Actions_Action->tp_clear(o); } else __Pyx_call_next_tp_clear(o, __pyx_tp_clear_6Cython_4Plex_7Actions_Begin);
  tmp = ((PyObject*)p->state_name);
  p->state_name = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  return 0;
}
