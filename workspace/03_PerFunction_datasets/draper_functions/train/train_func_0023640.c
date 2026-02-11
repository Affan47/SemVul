_wrap_svn_fs_access_get_username(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  char **arg1 = (char **) 0 ;
  svn_fs_access_t *arg2 = (svn_fs_access_t *) 0 ;
  char *temp1 ;
  PyObject * obj0 = 0 ;
  svn_error_t *result = 0 ;

  arg1 = &temp1;
  if (!PyArg_ParseTuple(args,(char *)"O:svn_fs_access_get_username",&obj0)) SWIG_fail;
  {
    arg2 = (svn_fs_access_t *)svn_swig_MustGetPtr(obj0, SWIGTYPE_p_svn_fs_access_t, svn_argnum_obj0);
    if (PyErr_Occurred()) {
      SWIG_fail;
    }
  }
  {
    svn_swig_py_release_py_lock();

    result = (svn_error_t *)svn_fs_access_get_username((char const **)arg1,arg2);

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
    PyObject *s;
    if (*arg1 == NULL) {
      Py_INCREF(Py_None);
      s = Py_None;
    }
    else {
      s = PyString_FromString(*arg1);
      if (s == NULL)
      SWIG_fail;
    }
    resultobj = SWIG_Python_AppendOutput(resultobj, s);
  }
  return resultobj;
fail:
  return NULL;
}
