_wrap_svn_repos_finish_report(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  void *arg1 = (void *) 0 ;
  apr_pool_t *arg2 = (apr_pool_t *) 0 ;
  apr_pool_t *_global_pool = NULL ;
  PyObject *_global_py_pool = NULL ;
  PyObject * obj0 = 0 ;
  PyObject * obj1 = 0 ;
  svn_error_t *result = 0 ;

  if (svn_swig_py_get_pool_arg(args, SWIGTYPE_p_apr_pool_t,
      &_global_py_pool, &_global_pool))
  SWIG_fail;
  arg2 = _global_pool;
  if (!PyArg_ParseTuple(args,(char *)"O|O:svn_repos_finish_report",&obj0,&obj1)) SWIG_fail;
  {
    if (obj0 == Py_None) {
      arg1 = NULL;
    } else if (SWIG_ConvertPtr(obj0, (void **) &arg1, 0, 0) == -1) {
      arg1 = (void *) obj0;
      PyErr_Clear();
    }
  }
  if (obj1) {

    if (obj1 != Py_None && obj1 != _global_py_pool) {
      SWIG_Python_TypeError(SWIG_TypePrettyName(SWIGTYPE_p_apr_pool_t), obj1);
      SWIG_arg_fail(svn_argnum_obj1);
      SWIG_fail;
    }
  }
  {
    svn_swig_py_release_py_lock();

    result = (svn_error_t *)svn_repos_finish_report(arg1,arg2);

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
