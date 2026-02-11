PyVTKMutableObject_Get(PyObject *self, PyObject *args)
{
  if (PyArg_ParseTuple(args, (char*)":get"))
    {
    PyObject *ob = PyVTKMutableObject_GetValue(self);
    Py_INCREF(ob);
    return ob;
    }

  return NULL;
}
