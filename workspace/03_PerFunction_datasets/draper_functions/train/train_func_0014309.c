_wrap_svn_client_status_t_changed_author_get(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  struct svn_client_status_t *arg1 = (struct svn_client_status_t *) 0 ;
  PyObject * obj0 = 0 ;
  char *result = 0 ;

  if (!PyArg_ParseTuple(args,(char *)"O:svn_client_status_t_changed_author_get",&obj0)) SWIG_fail;
  {
    arg1 = (struct svn_client_status_t *)svn_swig_MustGetPtr(obj0, SWIGTYPE_p_svn_client_status_t, svn_argnum_obj0);
    if (PyErr_Occurred()) {
      SWIG_fail;
    }
  }
  result = (char *) ((arg1)->changed_author);
  resultobj = SWIG_FromCharPtr((const char *)result);
  return resultobj;
fail:
  return NULL;
}
