gdpy_entry_setb(struct gdpy_entry_t* self, PyObject *value,
    void *closure)
{
  int i;
  int comp_scal = 0;
  double b[GD_MAX_LINCOM];
  double complex cb[GD_MAX_LINCOM];
  char *scalar[GD_MAX_LINCOM];

  dtrace("%p, %p, %p", self, value, closure);

  if (self->E->field_type != GD_LINCOM_ENTRY) {
    PyErr_Format(PyExc_AttributeError, "'pygetdata.entry' "
        "attribute 'b' not available for entry type %s",
        gdpy_entry_type_names[self->E->field_type]);
    dreturn("%i", -1);
    return -1;
  }

  if (!PyTuple_Check(value)) {
    PyErr_SetString(PyExc_TypeError, "'pygetdata.entry' "
        "attribute 'b' must be a tuple");
    dreturn("%i", -1);
    return -1;
  }

  if (PyTuple_Size(value) < self->E->n_fields) {
    PyErr_SetString(PyExc_TypeError, "'pygetdata.entry' "
        "not enough items in tuple for attribute 'b'");
    dreturn("%i", -1);
    return -1;
  }

  for (i = 0; i < self->E->n_fields; ++i) {
    PyObject *obj = PyTuple_GetItem(value, i);
    if (PyComplex_Check(obj)) {
      comp_scal = 1;
      b[i] = (double)(cb[i] = gdpy_as_complex(obj));
      scalar[i] = NULL;
    } else if (comp_scal) {
      gdpy_set_scalar_from_pyobj(obj, GD_COMPLEX128, scalar + i, cb + i);
      b[i] = creal(cb[i]);
    } else {
      gdpy_set_scalar_from_pyobj(obj, GD_FLOAT64, scalar + i, b + i);
      cb[i] = b[i];
    }
  }

  if (PyErr_Occurred()) {
    for (i = 0; i < GD_MAX_LINCOM; ++i)
      free(scalar[i]);
    dreturn("%i", -1);
    return -1;
  }

  for (i = 0; i < self->E->n_fields; ++i) {
    if (cimag(self->E->cm[i]))
      comp_scal = 1;
    self->E->cb[i] = cb[i];
    self->E->b[i] = b[i];
    free(self->E->scalar[i + GD_MAX_LINCOM]);
    self->E->scalar[i + GD_MAX_LINCOM] = scalar[i];
  }
  self->E->comp_scal = comp_scal;

  dreturn("%i", 0);
  return 0;
}
