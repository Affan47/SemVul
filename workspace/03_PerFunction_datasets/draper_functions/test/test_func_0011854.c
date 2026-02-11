PyVTKTemplate_Get(PyObject *ob, PyObject *args)
{
  PyObject *key = NULL;
  PyObject *def = Py_None;
  if (PyArg_ParseTuple(args, (char *)"O|O:get"))
    {
    ob = ((PyVTKTemplate *)ob)->dict;
    return PyObject_CallMethod(ob, (char *)"get", (char *)"(OO)", key, def);
    }
  return NULL;
}
