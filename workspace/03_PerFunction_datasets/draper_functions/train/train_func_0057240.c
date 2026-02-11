gdpy_dup_pystring(PyObject* obj)
{
  dtrace("%p", obj);
  char* s = PyString_AsString(obj);

  if (s != NULL) {
    s = strdup(s);

    if (s == NULL)
      PyErr_NoMemory();
  }

  dreturn("%p", s);
  return s;
}
