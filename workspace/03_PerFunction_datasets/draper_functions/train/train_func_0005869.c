_wrap_svn_diff_file_options_parse(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  svn_diff_file_options_t *arg1 = (svn_diff_file_options_t *) 0 ;
  apr_array_header_t *arg2 = (apr_array_header_t *) 0 ;
  apr_pool_t *arg3 = (apr_pool_t *) 0 ;
  apr_pool_t *_global_pool = NULL ;
  PyObject *_global_py_pool = NULL ;
  PyObject * obj0 = 0 ;
  PyObject * obj1 = 0 ;
  PyObject * obj2 = 0 ;
  svn_error_t *result = 0 ;

  if (svn_swig_py_get_pool_arg(args, SWIGTYPE_p_apr_pool_t,
      &_global_py_pool, &_global_pool))
  SWIG_fail;
  arg3 = _global_pool;
  if (!PyArg_ParseTuple(args,(char *)"OO|O:svn_diff_file_options_parse",&obj0,&obj1,&obj2)) SWIG_fail;
  {
    arg1 = (svn_diff_file_options_t *)svn_swig_MustGetPtr(obj0, SWIGTYPE_p_svn_diff_file_options_t, svn_argnum_obj0);
    if (PyErr_Occurred()) {
      SWIG_fail;
    }
  }
  {
    arg2 = (apr_array_header_t *) svn_swig_py_seq_to_array(obj1,
      sizeof(const char *),
      svn_swig_py_unwrap_string,
      NULL,
      _global_pool);
    if (PyErr_Occurred())
    SWIG_fail;
  }
  if (obj2) {

    if (obj2 != Py_None && obj2 != _global_py_pool) {
      SWIG_Python_TypeError(SWIG_TypePrettyName(SWIGTYPE_p_apr_pool_t), obj2);
      SWIG_arg_fail(svn_argnum_obj2);
      SWIG_fail;
    }
  }
  {
    svn_swig_py_release_py_lock();

    result = (svn_error_t *)svn_diff_file_options_parse(arg1,(apr_array_header_t const *)arg2,arg3);

    svn_swig_py_acquire_py_lock();

  }
  {
    if (result != NULL) {
      if (result->apr_err != SVN_ERR_SWIG_PY_EXCEPTION_SET)
      svn_swig_py_svn_exception(result);
      else
      svn_error_clear(result);
      SWIG_fail;
    }
    Py_INCREF(Py_None);
    resultobj = Py_None;
  }
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
