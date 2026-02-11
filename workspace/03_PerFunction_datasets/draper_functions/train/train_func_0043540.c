_wrap_svn_delta_editor_t_delete_entry_get(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  struct svn_delta_editor_t *arg1 = (struct svn_delta_editor_t *) 0 ;
  PyObject * obj0 = 0 ;
  svn_error_t *(*result)(char const *,svn_revnum_t,void *,apr_pool_t *) = 0 ;

  if (!PyArg_ParseTuple(args,(char *)"O:svn_delta_editor_t_delete_entry_get",&obj0)) SWIG_fail;
  {
    arg1 = (struct svn_delta_editor_t *)svn_swig_MustGetPtr(obj0, SWIGTYPE_p_svn_delta_editor_t, svn_argnum_obj0);
    if (PyErr_Occurred()) {
      SWIG_fail;
    }
  }
  result = (svn_error_t *(*)(char const *,svn_revnum_t,void *,apr_pool_t *)) ((arg1)->delete_entry);
  resultobj = SWIG_NewFunctionPtrObj((void *)(result), SWIGTYPE_p_f_p_q_const__char_svn_revnum_t_p_void_p_apr_pool_t__p_svn_error_t);
  return resultobj;
fail:
  return NULL;
}
