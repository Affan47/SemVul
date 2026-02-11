_wrap_svn_client_delete2(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  svn_commit_info_t **arg1 = (svn_commit_info_t **) 0 ;
  apr_array_header_t *arg2 = (apr_array_header_t *) 0 ;
  svn_boolean_t arg3 ;
  svn_client_ctx_t *arg4 = (svn_client_ctx_t *) 0 ;
  apr_pool_t *arg5 = (apr_pool_t *) 0 ;
  apr_pool_t *_global_pool = NULL ;
  PyObject *_global_py_pool = NULL ;
  svn_commit_info_t *temp1 = NULL ;
  PyObject * obj0 = 0 ;
  PyObject * obj1 = 0 ;
  PyObject * obj2 = 0 ;
  PyObject * obj3 = 0 ;
  svn_error_t *result = 0 ;

  if (svn_swig_py_get_pool_arg(args, SWIGTYPE_p_apr_pool_t,
      &_global_py_pool, &_global_pool))
  SWIG_fail;
  arg5 = _global_pool;
  arg1 = &temp1;
  if (!PyArg_ParseTuple(args,(char *)"OOO|O:svn_client_delete2",&obj0,&obj1,&obj2,&obj3)) SWIG_fail;
  {
    arg2 = (apr_array_header_t *) svn_swig_py_seq_to_array(obj0,
      sizeof(const char *),
      svn_swig_py_unwrap_string,
      NULL,
      _global_pool);
    if (PyErr_Occurred())
    SWIG_fail;
  }
  {
    arg3 = (svn_boolean_t)SWIG_As_long (obj1);
    if (SWIG_arg_fail(svn_argnum_obj1)) {
      SWIG_fail;
    }
  }
  {
    arg4 = (svn_client_ctx_t *)svn_swig_MustGetPtr(obj2, SWIGTYPE_p_svn_client_ctx_t, svn_argnum_obj2);
    if (PyErr_Occurred()) {
      SWIG_fail;
    }
  }
  if (obj3) {

    if (obj3 != Py_None && obj3 != _global_py_pool) {
      SWIG_Python_TypeError(SWIG_TypePrettyName(SWIGTYPE_p_apr_pool_t), obj3);
      SWIG_arg_fail(svn_argnum_obj3);
      SWIG_fail;
    }
  }
  {
    svn_swig_py_release_py_lock();

    result = (svn_error_t *)svn_client_delete2(arg1,(apr_array_header_t const *)arg2,arg3,arg4,arg5);

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
    resultobj = SWIG_Python_AppendOutput(resultobj, svn_swig_NewPointerObj(*arg1, SWIGTYPE_p_svn_commit_info_t,
        _global_py_pool, args))

    ;
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
