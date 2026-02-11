_wrap_svn_repos_link_path2(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  void *arg1 = (void *) 0 ;
  char *arg2 = (char *) 0 ;
  char *arg3 = (char *) 0 ;
  svn_revnum_t arg4 ;
  svn_boolean_t arg5 ;
  char *arg6 = (char *) 0 ;
  apr_pool_t *arg7 = (apr_pool_t *) 0 ;
  apr_pool_t *_global_pool = NULL ;
  PyObject *_global_py_pool = NULL ;
  PyObject * obj0 = 0 ;
  PyObject * obj3 = 0 ;
  PyObject * obj4 = 0 ;
  PyObject * obj6 = 0 ;
  svn_error_t *result = 0 ;

  if (svn_swig_py_get_pool_arg(args, SWIGTYPE_p_apr_pool_t,
      &_global_py_pool, &_global_pool))
  SWIG_fail;
  arg7 = _global_pool;
  if (!PyArg_ParseTuple(args,(char *)"OssOOz|O:svn_repos_link_path2",&obj0,&arg2,&arg3,&obj3,&obj4,&arg6,&obj6)) SWIG_fail;
  {
    if (obj0 == Py_None) {
      arg1 = NULL;
    } else if (SWIG_ConvertPtr(obj0, (void **) &arg1, 0, 0) == -1) {
      arg1 = (void *) obj0;
      PyErr_Clear();
    }
  }
  {
    arg4 = (svn_revnum_t)SWIG_As_long (obj3);
    if (SWIG_arg_fail(svn_argnum_obj3)) {
      SWIG_fail;
    }
  }
  {
    arg5 = (svn_boolean_t)SWIG_As_long (obj4);
    if (SWIG_arg_fail(svn_argnum_obj4)) {
      SWIG_fail;
    }
  }
  if (obj6) {

    if (obj6 != Py_None && obj6 != _global_py_pool) {
      SWIG_Python_TypeError(SWIG_TypePrettyName(SWIGTYPE_p_apr_pool_t), obj6);
      SWIG_arg_fail(svn_argnum_obj6);
      SWIG_fail;
    }
  }
  {
    svn_swig_py_release_py_lock();

    result = (svn_error_t *)svn_repos_link_path2(arg1,(char const *)arg2,(char const *)arg3,arg4,arg5,(char const *)arg6,arg7);

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
