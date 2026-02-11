PyCMOR_get_original_shape(PyObject *self,PyObject *args)
{
  int tmp,i,shape_array[CMOR_MAX_DIMENSIONS],var_id,blank_time;
  i=CMOR_MAX_DIMENSIONS;
  PyObject *mylist;
  if (!PyArg_ParseTuple(args,"ii",&var_id,&blank_time))
    return NULL;
  tmp = cmor_get_original_shape(&var_id,&shape_array[0],&i,blank_time);

  mylist = PyList_New(0);
  for (i=0;i<CMOR_MAX_DIMENSIONS;i++) {
    if (shape_array[i]!=-1) {
      PyList_Append(mylist,PyInt_FromLong(shape_array[i]));
    }
  }
  Py_INCREF(mylist);
  return mylist;
}
