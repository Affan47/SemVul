_wrap_svn_diff_fns2_invoke_datasource_get_next_token(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  svn_diff_fns2_t *arg1 = (svn_diff_fns2_t *) 0 ;
  apr_uint32_t *arg2 = (apr_uint32_t *) 0 ;
  void **arg3 = (void **) 0 ;
  void *arg4 = (void *) 0 ;
  svn_diff_datasource_e arg5 ;
  apr_uint32_t temp2 ;
  int res2 = SWIG_TMPOBJ ;
  void *temp3 ;
  PyObject * obj0 = 0 ;
  PyObject * obj1 = 0 ;
  PyObject * obj2 = 0 ;
  svn_error_t *result = 0 ;

  arg2 = &temp2;
  arg3 = &temp3;
  if (!PyArg_ParseTuple(args,(char *)"OOO:svn_diff_fns2_invoke_datasource_get_next_token",&obj0,&obj1,&obj2)) SWIG_fail;
  {
    arg1 = (svn_diff_fns2_t *)svn_swig_MustGetPtr(obj0, SWIGTYPE_p_svn_diff_fns2_t, svn_argnum_obj0);
    if (PyErr_Occurred()) {
      SWIG_fail;
    }
  }
  {
    if (obj1 == Py_None) {
      arg4 = NULL;
    } else if (SWIG_ConvertPtr(obj1, (void **) &arg4, 0, 0) == -1) {
      arg4 = (void *) obj1;
      PyErr_Clear();
    }
  }
  {
    arg5 = (svn_diff_datasource_e)SWIG_As_long (obj2);
    if (SWIG_arg_fail(svn_argnum_obj2)) {
      SWIG_fail;
    }
  }
  {
    svn_swig_py_release_py_lock();

    result = (svn_error_t *)svn_diff_fns2_invoke_datasource_get_next_token(arg1,arg2,arg3,arg4,arg5);

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
  if (SWIG_IsTmpObj(res2)) {
    resultobj = SWIG_Python_AppendOutput(resultobj, SWIG_From_unsigned_SS_long((*arg2)));
  } else {
    int new_flags = SWIG_IsNewObj(res2) ? (SWIG_POINTER_OWN |  0 ) :  0 ;
    resultobj = SWIG_Python_AppendOutput(resultobj, SWIG_NewPointerObj((void*)(arg2), SWIGTYPE_p_apr_uint32_t, new_flags));
  }
  {
    resultobj = SWIG_Python_AppendOutput(resultobj, svn_swig_NewPointerObj(*arg3, SWIGTYPE_p_void,
        _global_py_pool, args))

    ;
  }
  return resultobj;
fail:
  return NULL;
}
