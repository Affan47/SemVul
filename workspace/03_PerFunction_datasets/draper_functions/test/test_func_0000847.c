py_gc_locale_gets_list(PyObject* self, PyObject* args)
{
  PyObject *pylist;
  GList *result, *list ;


  if(!PyArg_ParseTuple(args, ":gcompris.get_locales_list"))
    return NULL;


  result = gc_locale_gets_list();

  pylist = PyList_New(0);

  for (list = result; list != NULL; list = list->next){
    PyList_Append( pylist, PyString_FromString(list->data));
  }

  Py_INCREF(pylist);
  return pylist;
}
