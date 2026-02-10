_wrap_svn_fs_change_txn_prop(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  svn_fs_txn_t *arg1 = (svn_fs_txn_t *) 0 ;
  char *arg2 = (char *) 0 ;
  svn_string_t *arg3 = (svn_string_t *) 0 ;
  apr_pool_t *arg4 = (apr_pool_t *) 0 ;
  apr_pool_t *_global_pool = NULL ;
  PyObject *_global_py_pool = NULL ;
  svn_string_t value3 ;
  PyObject * obj0 = 0 ;
  PyObject * obj2 = 0 ;
  PyObject * obj3 = 0 ;
  svn_error_t *result = 0 ;

  if (svn_swig_py_get_pool_arg(args, SWIGTYPE_p_apr_pool_t,
      &_global_py_pool, &_global_pool))
  SWIG_fail;
  arg4 = _global_pool;
  if (!PyArg_ParseTuple(args,(char *)"OsO|O:svn_fs_change_txn_prop",&obj0,&arg2,&obj2,&obj3)) SWIG_fail;
  {
    arg1 = (svn_fs_txn_t *)svn_swig_MustGetPtr(obj0, SWIGTYPE_p_svn_fs_txn_t, svn_argnum_obj0);
    if (PyErr_Occurred()) {
      SWIG_fail;
    }
  }
  {
    if (obj2 == Py_None)
    arg3 = NULL;
    else {
      if (!PyString_Check(obj2)) {
        PyErr_SetString(PyExc_TypeError, "not a string");
        SWIG_fail;
      }
      value3.data = PyString_AS_STRING(obj2);
      value3.len = PyString_GET_SIZE(obj2);
      arg3 = &value3;
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

    result = (svn_error_t *)svn_fs_change_txn_prop(arg1,(char const *)arg2,(struct svn_string_t const *)arg3,arg4);

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
