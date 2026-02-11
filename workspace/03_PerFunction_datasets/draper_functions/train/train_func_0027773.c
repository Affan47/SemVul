_wrap_svn_delta_default_editor(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  apr_pool_t *arg1 = (apr_pool_t *) 0 ;
  apr_pool_t *_global_pool = NULL ;
  PyObject *_global_py_pool = NULL ;
  PyObject * obj0 = 0 ;
  svn_delta_editor_t *result = 0 ;

  if (svn_swig_py_get_pool_arg(args, SWIGTYPE_p_apr_pool_t,
      &_global_py_pool, &_global_pool))
  SWIG_fail;
  arg1 = _global_pool;
  if (!PyArg_ParseTuple(args,(char *)"|O:svn_delta_default_editor",&obj0)) SWIG_fail;
  if (obj0) {

    if (obj0 != Py_None && obj0 != _global_py_pool) {
      SWIG_Python_TypeError(SWIG_TypePrettyName(SWIGTYPE_p_apr_pool_t), obj0);
      SWIG_arg_fail(svn_argnum_obj0);
      SWIG_fail;
    }
  }
  {
    svn_swig_py_release_py_lock();

    result = (svn_delta_editor_t *)svn_delta_default_editor(arg1);

    svn_swig_py_acquire_py_lock();

  }
  resultobj = svn_swig_NewPointerObj((void*)(result), SWIGTYPE_p_svn_delta_editor_t,
    _global_py_pool, args);
  {
    Py_XDECREF(_global_py_pool);
  }
  return resultobj;
fail:
  {
    Py_XDECREF(_global_py_pool);
  }
  return NULL;
}
