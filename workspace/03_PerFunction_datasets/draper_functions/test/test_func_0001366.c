gdpy_dirfile_getnvectors(struct gdpy_dirfile_t* self)
{
  dtrace("%p", self);

  unsigned int nvectors = gd_nvectors(self->D);

  PYGD_CHECK_ERROR(self->D, NULL);

  PyObject* pynvectors = PyInt_FromLong((long)nvectors);

  dreturn("%p", pynvectors);
  return pynvectors;
}
