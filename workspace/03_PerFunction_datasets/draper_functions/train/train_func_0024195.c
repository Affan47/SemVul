gdpy_entry_getspf(struct gdpy_entry_t* self, void* closure)
{
  PyObject* obj = NULL;

  dtrace("%p, %p", self, closure);

  if (self->E->field_type == GD_RAW_ENTRY) {
    if (self->E->scalar[0] == NULL)
      obj = PyInt_FromLong(self->E->spf);
    else
      obj = PyString_FromString(self->E->scalar[0]);
  } else
    PyErr_Format(PyExc_AttributeError, "'pygetdata.entry' "
        "attribute 'spf' not available for entry type %s",
        gdpy_entry_type_names[self->E->field_type]);

  dreturn("%p", obj);
  return obj;
}
