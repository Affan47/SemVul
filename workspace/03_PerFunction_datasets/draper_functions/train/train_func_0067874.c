_wrap_svn_client_invoke_diff_summarize_func(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  svn_client_diff_summarize_func_t arg1 = (svn_client_diff_summarize_func_t) 0 ;
  svn_client_diff_summarize_t *arg2 = (svn_client_diff_summarize_t *) 0 ;
  void *arg3 = (void *) 0 ;
  apr_pool_t *arg4 = (apr_pool_t *) 0 ;
  apr_pool_t *_global_pool = NULL ;
  PyObject *_global_py_pool = NULL ;
  PyObject * obj0 = 0 ;
  PyObject * obj1 = 0 ;
  PyObject * obj2 = 0 ;
  PyObject * obj3 = 0 ;
  svn_error_t *result = 0 ;

  if (svn_swig_py_get_pool_arg(args, SWIGTYPE_p_apr_pool_t,
      &_global_py_pool, &_global_pool))
  SWIG_fail;
  arg4 = _global_pool;
  if (!PyArg_ParseTuple(args,(char *)"OOO|O:svn_client_invoke_diff_summarize_func",&obj0,&obj1,&obj2,&obj3)) SWIG_fail;
  {
    svn_client_diff_summarize_func_t * tmp =
    svn_swig_MustGetPtr(obj0, SWIGTYPE_p_p_f_p_q_const__svn_client_diff_summarize_t_p_void_p_apr_pool_t__p_svn_error_t, svn_argnum_obj0);
    if (tmp == NULL || PyErr_Occurred()) {
      SWIG_fail;
    }
    arg1 = *tmp;
  }
  {
    arg2 = (svn_client_diff_summarize_t *)svn_swig_MustGetPtr(obj1, SWIGTYPE_p_svn_client_diff_summarize_t, svn_argnum_obj1);
    if (PyErr_Occurred()) {
      SWIG_fail;
    }
  }
  {
    if (obj2 == Py_None) {
      arg3 = NULL;
    } else if (SWIG_ConvertPtr(obj2, (void **) &arg3, 0, 0) == -1) {
      arg3 = (void *) obj2;
      PyErr_Clear();
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

    result = (svn_error_t *)svn_client_invoke_diff_summarize_func(arg1,(struct svn_client_diff_summarize_t const *)arg2,arg3,arg4);

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
