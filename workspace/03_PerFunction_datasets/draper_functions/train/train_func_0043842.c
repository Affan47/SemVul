_wrap_new_lfc_direnrep(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  struct lfc_direnrep *result = 0 ;

  if (!PyArg_ParseTuple(args,(char *)":new_lfc_direnrep")) SWIG_fail;

  char serrbuf[ERRORLEN_MAX] = "";
  lfc_seterrbuf (serrbuf, ERRORLEN_MAX);
  Py_BEGIN_ALLOW_THREADS
  result = (struct lfc_direnrep *)calloc(1, sizeof(struct lfc_direnrep));
  Py_END_ALLOW_THREADS

  {
    PyObject *myresult;


    int PYTHON_OWNED=0;


    if (result == 0) {
      Py_INCREF (Py_None);
      myresult = Py_None;
    }

    else {

      myresult = SWIG_NewPointerObj (result, SWIGTYPE_p_lfc_direnrep, PYTHON_OWNED);
    }

    resultobj = my_t_output_helper(NULL, myresult);
  }
  return resultobj;
fail:
  return NULL;
}
