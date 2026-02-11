_wrap_svn_repos_fs_get_locks(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  apr_hash_t **arg1 = (apr_hash_t **) 0 ;
  svn_repos_t *arg2 = (svn_repos_t *) 0 ;
  char *arg3 = (char *) 0 ;
  svn_repos_authz_func_t arg4 = (svn_repos_authz_func_t) 0 ;
  void *arg5 = (void *) 0 ;
  apr_pool_t *arg6 = (apr_pool_t *) 0 ;
  apr_pool_t *_global_pool = NULL ;
  PyObject *_global_py_pool = NULL ;
  apr_hash_t *temp1 ;
  PyObject * obj0 = 0 ;
  PyObject * obj2 = 0 ;
  PyObject * obj3 = 0 ;
  svn_error_t *result = 0 ;

  if (svn_swig_py_get_pool_arg(args, SWIGTYPE_p_apr_pool_t,
      &_global_py_pool, &_global_pool))
  SWIG_fail;
  arg6 = _global_pool;
  arg1 = &temp1;
  if (!PyArg_ParseTuple(args,(char *)"OsO|O:svn_repos_fs_get_locks",&obj0,&arg3,&obj2,&obj3)) SWIG_fail;
  {
    arg2 = (svn_repos_t *)svn_swig_MustGetPtr(obj0, SWIGTYPE_p_svn_repos_t, svn_argnum_obj0);
    if (PyErr_Occurred()) {
      SWIG_fail;
    }
  }
  {

    arg4 = svn_swig_py_repos_authz_func;
    arg5 = obj2;
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

    result = (svn_error_t *)svn_repos_fs_get_locks(arg1,arg2,(char const *)arg3,arg4,arg5,arg6);

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
    resultobj = SWIG_Python_AppendOutput(resultobj, svn_swig_py_convert_hash(*arg1,
        SWIGTYPE_p_svn_lock_t,
        _global_py_pool))


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
