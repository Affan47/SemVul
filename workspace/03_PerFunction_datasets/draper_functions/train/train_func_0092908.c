_wrap_svn_fs_unparse_id(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  svn_fs_id_t *arg1 = (svn_fs_id_t *) 0 ;
  apr_pool_t *arg2 = (apr_pool_t *) 0 ;
  apr_pool_t *_global_pool = NULL ;
  PyObject *_global_py_pool = NULL ;
  PyObject * obj0 = 0 ;
  PyObject * obj1 = 0 ;
  svn_string_t *result = 0 ;

  if (svn_swig_py_get_pool_arg(args, SWIGTYPE_p_apr_pool_t,
      &_global_py_pool, &_global_pool))
  SWIG_fail;
  arg2 = _global_pool;
  if (!PyArg_ParseTuple(args,(char *)"O|O:svn_fs_unparse_id",&obj0,&obj1)) SWIG_fail;
  {
    arg1 = (svn_fs_id_t *)svn_swig_MustGetPtr(obj0, SWIGTYPE_p_svn_fs_id_t, svn_argnum_obj0);
    if (PyErr_Occurred()) {
      SWIG_fail;
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

    result = (svn_string_t *)svn_fs_unparse_id((struct svn_fs_id_t const *)arg1,arg2);

    svn_swig_py_acquire_py_lock();

  }
  {
    resultobj = PyString_FromStringAndSize(result->data, result->len);
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
