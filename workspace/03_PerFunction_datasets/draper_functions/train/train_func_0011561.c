_wrap_lfc_client_setVOMS_data(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  char *arg1 = (char *) 0 ;
  char **arg2 = (char **) 0 ;
  int arg3 ;
  PyObject * obj0 = 0 ;
  PyObject * obj1 = 0 ;
  RETURNCODE result;

  if (!PyArg_ParseTuple(args,(char *)"OO:lfc_client_setVOMS_data",&obj0,&obj1)) SWIG_fail;
  {
    if (obj0 == Py_None) {
      arg1 = NULL;
    } else {
      arg1 = PyString_AsString (obj0);
      if (arg1 && arg1[0] == 0) arg1 = NULL;
    }
  }
  {
    int i;

    if (!PyList_Check (obj1)) {
      PyErr_SetString (PyExc_ValueError, "Expecting a list");
      return NULL;
    }
    arg3 = PyList_Size (obj1);
    arg2 = (char **) calloc (arg3+1, sizeof (char *));
    for (i = 0; i < arg3; i++) {
      PyObject *s = PyList_GetItem (obj1,i);
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
  result = (RETURNCODE)lfc_client_setVOMS_data(arg1,arg2,arg3);
  Py_END_ALLOW_THREADS

  if (result < 0) {
    PyErr_SetString (serrno2pyexc (serrno), serrbuf);
    return (NULL);
  }

  is_returncode = 1;
  resultobj = Py_None;
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
