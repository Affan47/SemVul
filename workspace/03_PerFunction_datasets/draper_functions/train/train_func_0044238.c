SWIG_Python_GetSwigThis(PyObject *pyobj)
{
  PyObject *obj;

  if (SwigPyObject_Check(pyobj))
    return (SwigPyObject *) pyobj;

#ifdef SWIGPYTHON_BUILTIN
  (void)obj;
# ifdef PyWeakref_CheckProxy
  if (PyWeakref_CheckProxy(pyobj)) {
    pyobj = PyWeakref_GET_OBJECT(pyobj);
    if (pyobj && SwigPyObject_Check(pyobj))
      return (SwigPyObject*) pyobj;
  }
# endif
  return NULL;
#else

  obj = 0;

#if (!defined(SWIG_PYTHON_SLOW_GETSET_THIS) && (PY_VERSION_HEX >= 0x02030000))
  if (PyInstance_Check(pyobj)) {
    obj = _PyInstance_Lookup(pyobj, SWIG_This());
  } else {
    PyObject **dictptr = _PyObject_GetDictPtr(pyobj);
    if (dictptr != NULL) {
      PyObject *dict = *dictptr;
      obj = dict ? PyDict_GetItem(dict, SWIG_This()) : 0;
    } else {
#ifdef PyWeakref_CheckProxy
      if (PyWeakref_CheckProxy(pyobj)) {
	PyObject *wobj = PyWeakref_GET_OBJECT(pyobj);
	return wobj ? SWIG_Python_GetSwigThis(wobj) : 0;
      }
#endif
      obj = PyObject_GetAttr(pyobj,SWIG_This());
      if (obj) {
	Py_DECREF(obj);
      } else {
	if (PyErr_Occurred()) PyErr_Clear();
	return 0;
      }
    }
  }
#else
  obj = PyObject_GetAttr(pyobj,SWIG_This());
  if (obj) {
    Py_DECREF(obj);
  } else {
    if (PyErr_Occurred()) PyErr_Clear();
    return 0;
  }
#endif
  if (obj && !SwigPyObject_Check(obj)) {


    return SWIG_Python_GetSwigThis(obj);
  }
  return (SwigPyObject *)obj;
#endif
}
