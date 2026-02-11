gdpy_dirfile_getnmvectors(struct gdpy_dirfile_t* self,
    PyObject* args, PyObject* keys)
{
  dtrace("%p, %p, %p", self, args, keys);

  char* keywords[] = { "parent", NULL };
  const char* parent = NULL;

  if (!PyArg_ParseTupleAndKeywords(args, keys,
        "s:pygetdata.dirfile.nmvectors", keywords, &parent))
  {
    dreturn("%p", NULL);
    return NULL;
  }

  unsigned int nmvectors = gd_nmvectors(self->D, parent);

  PYGD_CHECK_ERROR(self->D, NULL);

  PyObject* pyobj = PyInt_FromLong((long)nmvectors);

  dreturn("%p", pyobj);
  return pyobj;
}
