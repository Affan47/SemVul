_wrap_dpm_getpoolfs(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  char *arg1 = (char *) 0 ;
  int *arg2 = (int *) 0 ;
  struct dpm_fs **arg3 = (struct dpm_fs **) 0 ;
  PyObject * obj0 = 0 ;
  RETURNCODE result;

  {
    int tmp_int;
    struct dpm_fs *tmp_struct;
    arg2 = &tmp_int;
    arg3 = &tmp_struct;
  }
  if (!PyArg_ParseTuple(args,(char *)"O:dpm_getpoolfs",&obj0)) SWIG_fail;
  {
    if (obj0 == Py_None) {
      arg1 = NULL;
    } else {
      arg1 = PyString_AsString (obj0);
      if (arg1 && arg1[0] == 0) arg1 = NULL;
    }
  }
  result = (RETURNCODE)dpm_getpoolfs(arg1,arg2,arg3);
  if (result < 0) {
    PyErr_SetString (serrno2pyexc (serrno), serrbuf);
    return (NULL);
  }

  is_returncode = 1;
  resultobj = Py_None;
  {
    PyObject *myresult;


    if(result < 0){
      Py_INCREF(Py_None);
      myresult = Py_None;
    }

    else{
      int i;
      myresult = PyList_New(*arg2);

      for (i = 0; i < *arg2; ++i) {

        int PYTHON_OWNED = i > 0 ? 0 : 1;

        struct dpm_fs * aux = (struct dpm_fs *) (*arg3)+i;


        PyObject * aux_obj = SWIG_NewPointerObj(aux, SWIGTYPE_p_dpm_fs, PYTHON_OWNED);


        PyList_SetItem(myresult, i, aux_obj);

      }
    }

    resultobj = my_t_output_helper(resultobj, myresult);
  }
  return resultobj;
fail:
  return NULL;
}
