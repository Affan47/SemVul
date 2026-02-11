gdpy_dirfile_delentry(struct gdpy_dirfile_t* self,
    void* args, void* keys)
{
  dtrace("%p, %p, %p", self, args, keys);

  char* keywords[] = {"field_code", "flags", NULL};
  const char* field_code;
  int flags = 0;

  if (!PyArg_ParseTupleAndKeywords(args, keys,
        "s|i:pygetdata.dirfile.delete", keywords, &field_code, &flags))
  {
    dreturn("%p", NULL);
    return NULL;
  }

  gd_delete(self->D, field_code, flags);

  PYGD_CHECK_ERROR(self->D, NULL);

  Py_INCREF(Py_None);
  dreturn("%p", Py_None);
  return Py_None;
}
