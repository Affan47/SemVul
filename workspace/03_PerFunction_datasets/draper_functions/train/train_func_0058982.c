_wrap_svn_ra_plugin_invoke_rev_proplist(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  svn_ra_plugin_t *arg1 = (svn_ra_plugin_t *) 0 ;
  void *arg2 = (void *) 0 ;
  svn_revnum_t arg3 ;
  apr_hash_t **arg4 = (apr_hash_t **) 0 ;
  apr_pool_t *arg5 = (apr_pool_t *) 0 ;
  apr_pool_t *_global_pool = NULL ;
  PyObject *_global_py_pool = NULL ;
  apr_hash_t *temp4 ;
  PyObject * obj0 = 0 ;
  PyObject * obj1 = 0 ;
  PyObject * obj2 = 0 ;
  PyObject * obj3 = 0 ;
  svn_error_t *result = 0 ;

  if (svn_swig_py_get_pool_arg(args, SWIGTYPE_p_apr_pool_t,
      &_global_py_pool, &_global_pool))
  SWIG_fail;
  arg5 = _global_pool;
  arg4 = &temp4;
  if (!PyArg_ParseTuple(args,(char *)"OOO|O:svn_ra_plugin_invoke_rev_proplist",&obj0,&obj1,&obj2,&obj3)) SWIG_fail;
  {
    arg1 = (svn_ra_plugin_t *)svn_swig_MustGetPtr(obj0, SWIGTYPE_p_svn_ra_plugin_t, svn_argnum_obj0);
    if (PyErr_Occurred()) {
      SWIG_fail;
    }
  }
  {
    if (obj1 == Py_None) {
      arg2 = NULL;
    } else if (SWIG_ConvertPtr(obj1, (void **) &arg2, 0, 0) == -1) {
      arg2 = (void *) obj1;
      PyErr_Clear();
    }
  }
  {
    arg3 = (svn_revnum_t)SWIG_As_long (obj2);
    if (SWIG_arg_fail(svn_argnum_obj2)) {
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

    result = (svn_error_t *)svn_ra_plugin_invoke_rev_proplist(arg1,arg2,arg3,arg4,arg5);

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
    resultobj = SWIG_Python_AppendOutput(resultobj, svn_swig_py_prophash_to_dict(*arg4));
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
