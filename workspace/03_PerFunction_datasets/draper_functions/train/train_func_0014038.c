_wrap_lfc_getgrpmap(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  int *arg1 = (int *) 0 ;
  struct lfc_groupinfo **arg2 = (struct lfc_groupinfo **) 0 ;
  int result;

  {
    int tmp_int;
    struct lfc_groupinfo *tmp_struct;
    arg1 = &tmp_int;
    arg2 = &tmp_struct;
  }
  if (!PyArg_ParseTuple(args,(char *)":lfc_getgrpmap")) SWIG_fail;
  {
    Py_BEGIN_ALLOW_THREADS
    result = (int)lfc_getgrpmap(arg1,arg2);
    Py_END_ALLOW_THREADS
  }
  {
    resultobj = PyInt_FromLong(result);
  }
  {
    PyObject *tuple;


    if(PyInt_AsLong(resultobj) != 0){
      tuple = PyTuple_New(1);
      Py_INCREF(Py_None);
      PyTuple_SetItem(tuple, 0, Py_None);
      PyObject * old_result = resultobj;
      resultobj = PyTuple_New(2);
      PyTuple_SetItem(resultobj, 0, old_result);
      PyTuple_SetItem(resultobj, 1, tuple);
    }

    else{
      tuple = PyTuple_New(*arg1);

      int i;
      for(i=0; i<*arg1; i++){

        int PYTHON_OWNED = i>0 ? 0 : 1;

        struct lfc_groupinfo * aux = (struct lfc_groupinfo *) (*arg2)+i;


        PyObject * aux_obj = SWIG_NewPointerObj(aux, SWIGTYPE_p_lfc_groupinfo, PYTHON_OWNED);


        PyTuple_SetItem(tuple, i, aux_obj);

      }
      PyObject * old_result = resultobj;


      resultobj = PyTuple_New(2);
      PyTuple_SetItem(resultobj, 0, old_result);
      PyTuple_SetItem(resultobj, 1, tuple);

    }
  }
  return resultobj;
fail:
  return NULL;
}
