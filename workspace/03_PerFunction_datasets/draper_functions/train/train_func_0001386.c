_wrap_lfc_registerfiles(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  int arg1 ;
  struct lfc_filereg *arg2 = (struct lfc_filereg *) 0 ;
  int *arg3 = (int *) 0 ;
  int **arg4 = (int **) 0 ;
  PyObject * obj0 = 0 ;
  RETURNCODE result;

  {
    int tmp_int;
    int *tmp_tab;
    arg3 = &tmp_int;
    arg4 = &tmp_tab;
  }
  if (!PyArg_ParseTuple(args,(char *)"O:lfc_registerfiles",&obj0)) SWIG_fail;
  {

    if (!PyList_Check (obj0)) {
      PyErr_SetString (PyExc_ValueError, "Expecting a list");
      return NULL;
    }


    else {

      arg1 = PyList_Size (obj0);


      arg2 = (struct lfc_filereg *) calloc (arg1, sizeof (struct lfc_filereg)) ;

      int i;
      for (i=0; i<arg1; i++) {
        PyObject * aux_object = PyList_GetItem (obj0, i);


        struct lfc_filereg * aux_p;


        SWIG_ConvertPtr (aux_object, (void**) &aux_p,
          SWIGTYPE_p_lfc_filereg, SWIG_POINTER_EXCEPTION);


        arg2[i] = *aux_p;
      }

    }

  }
  result = (RETURNCODE)lfc_registerfiles(arg1,arg2,arg3,arg4);
  if (result < 0) {
    PyErr_SetString (serrno2pyexc (serrno), serrbuf);
    return (NULL);
  }

  is_returncode = 1;
  resultobj = Py_None;
  {
    PyObject *myresult;


    if (result < 0 || *arg3 < 0) {
      Py_INCREF (Py_None);
      myresult = Py_None;
    }

    else {
      int i;
      PyObject *aux_obj;
      myresult = PyList_New (*arg3);

      for (i = 0; i < *arg3; i++) {
        aux_obj = PyInt_FromLong ((long) (*arg4)[i]);
        PyList_SetItem (myresult, i, aux_obj);
      }
    }

    resultobj = my_t_output_helper(resultobj, myresult);
  }
  {
    if (arg2) free (arg2);
  }
  return resultobj;
fail:
  {
    if (arg2) free (arg2);
  }
  return NULL;
}
