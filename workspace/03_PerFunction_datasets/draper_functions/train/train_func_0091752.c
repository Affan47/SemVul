_wrap_svn_client_version(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  svn_version_t *result = 0 ;

  if (!PyArg_ParseTuple(args,(char *)":svn_client_version")) SWIG_fail;
  {
    svn_swig_py_release_py_lock();

    result = (svn_version_t *)svn_client_version();

    svn_swig_py_acquire_py_lock();

  }
  resultobj = svn_swig_NewPointerObj((void*)(result), SWIGTYPE_p_svn_version_t,
    _global_py_pool, args);
  return resultobj;
fail:
  return NULL;
}
