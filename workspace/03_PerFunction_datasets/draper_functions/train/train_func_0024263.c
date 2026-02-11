_wrap_svn_repos_parse_fns3_invoke_close_node(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  svn_repos_parse_fns3_t *arg1 = (svn_repos_parse_fns3_t *) 0 ;
  void *arg2 = (void *) 0 ;
  PyObject * obj0 = 0 ;
  PyObject * obj1 = 0 ;
  svn_error_t *result = 0 ;

  if (!PyArg_ParseTuple(args,(char *)"OO:svn_repos_parse_fns3_invoke_close_node",&obj0,&obj1)) SWIG_fail;
  {
    arg1 = (svn_repos_parse_fns3_t *)svn_swig_MustGetPtr(obj0, SWIGTYPE_p_svn_repos_parse_fns3_t, svn_argnum_obj0);
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
    svn_swig_py_release_py_lock();

    result = (svn_error_t *)svn_repos_parse_fns3_invoke_close_node(arg1,arg2);

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
  return resultobj;
fail:
  return NULL;
}
