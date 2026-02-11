py_gc_board_conf_separator(PyObject* self, PyObject* args)
{
  PyObject *py_bconf;
  pyGcomprisBoardConfigObject * bconf;


  if(!PyArg_ParseTuple(args, "O:gc_board_conf_separator", &py_bconf))
    return NULL;

  bconf = (pyGcomprisBoardConfigObject*)py_bconf;


  return (PyObject *)pygobject_new((GObject*) gc_board_conf_separator(bconf->cdata));

}
