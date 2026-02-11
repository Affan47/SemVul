py_sugar_save (PyObject* self, PyObject* args)
{
  gchar *filename;

  if(!PyArg_ParseTuple(args, "s:gcompris.sugar_save", &filename))
    return NULL;


  sugar_save (filename);
  Py_INCREF(Py_None);
  return Py_None;
}
