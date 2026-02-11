_wrap_C__lfc_errno(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  int *result = 0 ;

  if (!PyArg_ParseTuple(args,(char *)":C__lfc_errno")) SWIG_fail;

  char serrbuf[ERRORLEN_MAX] = "";
  lfc_seterrbuf (serrbuf, ERRORLEN_MAX);
  Py_BEGIN_ALLOW_THREADS
  result = (int *)C__lfc_errno();
  Py_END_ALLOW_THREADS

  resultobj = SWIG_NewPointerObj(SWIG_as_voidptr(result), SWIGTYPE_p_int, 0 |  0 );
  return resultobj;
fail:
  return NULL;
}
