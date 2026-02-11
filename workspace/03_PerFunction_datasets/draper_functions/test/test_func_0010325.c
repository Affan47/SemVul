is_empty(PyObject * self, PyObject * args)
{
  PyObject * p;

  if (!PyArg_ParseTuple(args, "O", &p)) {
    return NULL;
  }

  const ImmutableComparison * cmp;

  cmp = (ImmutableComparison *) PyCObject_AsVoidPtr(p);

  int answer = 0;
  if (cmp->is_empty()) {
    answer = 1;
  }

  return Py_BuildValue("i", answer);
}
