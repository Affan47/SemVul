_wrap_svn_fs_copy(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  svn_fs_root_t *arg1 = (svn_fs_root_t *) 0 ;
  char *arg2 = (char *) 0 ;
  svn_fs_root_t *arg3 = (svn_fs_root_t *) 0 ;
  char *arg4 = (char *) 0 ;
  apr_pool_t *arg5 = (apr_pool_t *) 0 ;
  apr_pool_t *_global_pool = NULL ;
  PyObject *_global_py_pool = NULL ;
  PyObject * obj0 = 0 ;
  PyObject * obj2 = 0 ;
  PyObject * obj4 = 0 ;
  svn_error_t *result = 0 ;

  if (svn_swig_py_get_pool_arg(args, SWIGTYPE_p_apr_pool_t,
      &_global_py_pool, &_global_pool))
  SWIG_fail;
  arg5 = _global_pool;
  if (!PyArg_ParseTuple(args,(char *)"OsOs|O:svn_fs_copy",&obj0,&arg2,&obj2,&arg4,&obj4)) SWIG_fail;
  {
    arg1 = (svn_fs_root_t *)svn_swig_MustGetPtr(obj0, SWIGTYPE_p_svn_fs_root_t, svn_argnum_obj0);
    if (PyErr_Occurred()) {
      SWIG_fail;
    }
  }
  {
    arg3 = (svn_fs_root_t *)svn_swig_MustGetPtr(obj2, SWIGTYPE_p_svn_fs_root_t, svn_argnum_obj2);
    if (PyErr_Occurred()) {
      SWIG_fail;
    }
  }
  if (obj4) {

    if (obj4 != Py_None && obj4 != _global_py_pool) {
      SWIG_Python_TypeError(SWIG_TypePrettyName(SWIGTYPE_p_apr_pool_t), obj4);
      SWIG_arg_fail(svn_argnum_obj4);
      SWIG_fail;
    }
  }
  {
    svn_swig_py_release_py_lock();

    result = (svn_error_t *)svn_fs_copy(arg1,(char const *)arg2,arg3,(char const *)arg4,arg5);

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
