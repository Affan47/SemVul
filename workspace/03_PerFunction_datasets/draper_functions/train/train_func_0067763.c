_wrap_lfc_getreplicass(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  int arg1 ;
  char **arg2 = (char **) 0 ;
  int *arg3 = (int *) 0 ;
  struct lfc_filereplicas **arg4 = (struct lfc_filereplicas **) 0 ;
  PyObject * obj0 = 0 ;
  RETURNCODE result;

  {
    int tmp_int;
    struct lfc_filereplicas *tmp_struct;
    arg3 = &tmp_int;
    arg4 = &tmp_struct;
  }
  if (!PyArg_ParseTuple(args,(char *)"O:lfc_getreplicass",&obj0)) SWIG_fail;
  {
    int i;

    if (!PyList_Check (obj0)) {
      PyErr_SetString (PyExc_ValueError, "Expecting a list");
      return NULL;
    }
    arg1 = PyList_Size (obj0);
    arg2 = (char **) calloc (arg1+1, sizeof (char *));
    for (i = 0; i < arg1; i++) {
      PyObject *s = PyList_GetItem (obj0,i);
      if (!PyString_Check (s)) {
        free (arg2);
        PyErr_SetString (PyExc_ValueError, "List items must be strings");
        return NULL;
      }
      arg2[i] = PyString_AsString (s);
    }
    arg2[i] = 0;
  }

  char serrbuf[ERRORLEN_MAX] = "";
  lfc_seterrbuf (serrbuf, ERRORLEN_MAX);
  Py_BEGIN_ALLOW_THREADS
  result = (RETURNCODE)lfc_getreplicass(arg1,(char const **)arg2,arg3,arg4);
  Py_END_ALLOW_THREADS

  if (result < 0) {
    PyErr_SetString (serrno2pyexc (serrno), serrbuf);
    return (NULL);
  }

  is_returncode = 1;
  resultobj = Py_None;
  {
    PyObject *myresult;


    if (result < 0) {
      Py_INCREF (Py_None);
      myresult = Py_None;
    }

    else {
      myresult = PyList_New (*arg3);

      int i;
      for (i = 0; i < *arg3; i++) {

        int PYTHON_OWNED = i > 0 ? 0 : 1;

        struct lfc_filereplicas * aux = (struct lfc_filereplicas *) (*arg4)+i;


        PyObject * aux_obj = SWIG_NewPointerObj (aux, SWIGTYPE_p_lfc_filereplicas, PYTHON_OWNED);


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
