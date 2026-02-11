gdpy_dirfile_add(struct gdpy_dirfile_t* self,
    PyObject* args, PyObject* keys)
{
  dtrace("%p, %p, %p", self, args, keys);

  char* keywords[] = { "entry", NULL };
  struct gdpy_entry_t* entry = NULL;

  if (!PyArg_ParseTupleAndKeywords(args, keys, "O!:pygetdata.dirfile.add",
        keywords, &gdpy_entry, &entry))
  {
    dreturn("%p", NULL);
    return NULL;
  }

  gd_add(self->D, entry->E);

  PYGD_CHECK_ERROR(self->D, NULL);

  Py_INCREF(Py_None);
  dreturn("%p", Py_None);
  return Py_None;
}
