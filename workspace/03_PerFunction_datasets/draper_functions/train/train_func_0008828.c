gdpy_fragment_setprotection(struct gdpy_fragment_t* self,
    PyObject *value, void *closure)
{
  dtrace("%p, %p, %p", self, value, closure);

  int p = PyInt_AsLong(value);

  if (PyErr_Occurred()) {
    dreturn("%i", -1);
    return -1;
  }

  gd_alter_protection(self->dirfile->D, p, self->n);

  PYGD_CHECK_ERROR(self->dirfile->D, -1);

  dreturn("%i", 0);
  return 0;
}
