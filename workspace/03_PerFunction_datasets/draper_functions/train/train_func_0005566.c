_wrap_lfc_getgrpmap(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  int *arg1 = (int *) 0 ;
  struct lfc_groupinfo **arg2 = (struct lfc_groupinfo **) 0 ;
  RETURNCODE result;

  {
    int tmp_int;
    struct lfc_groupinfo *tmp_struct;
    arg1 = &tmp_int;
    arg2 = &tmp_struct;
  }
  if (!PyArg_ParseTuple(args,(char *)":lfc_getgrpmap")) SWIG_fail;
  result = (RETURNCODE)lfc_getgrpmap(arg1,arg2);
  if (result < 0) {
    PyErr_SetString (serrno2pyexc (serrno), serrbuf);
    return (NULL);
  }

  is_returncode = 1;
  resultobj = Py_None;
  {
    PyObject *myresult;


    if (result < 0 || *arg1 < 0) {
      Py_INCREF (Py_None);
      myresult = Py_None;
    }

    else {
      int i;
      myresult = PyList_New (*arg1);

      for (i = 0; i < *arg1; i++) {

        int PYTHON_OWNED = i > 0 ? 0 : 1;

        struct lfc_groupinfo * aux = (struct lfc_groupinfo *) (*arg2)+i;


        PyObject * aux_obj = SWIG_NewPointerObj (aux, SWIGTYPE_p_lfc_groupinfo, PYTHON_OWNED);


        PyList_SetItem (myresult, i, aux_obj);
      }
    }

    resultobj = my_t_output_helper(resultobj, myresult);
  }
  return resultobj;
fail:
  return NULL;
}
