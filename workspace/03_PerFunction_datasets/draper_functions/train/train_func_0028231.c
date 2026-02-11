Py_filter_init (Py_filter * self, PyObject * args, PyObject * kwds)
{
  self->o = new_aubio_filter (self->order);
  if (self->o == NULL) {
    return -1;
  }

  return 0;
}
