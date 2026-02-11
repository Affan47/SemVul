Py_filterbank_set_coeffs (Py_filterbank * self, PyObject *args)
{
  uint_t err = 0;

  PyObject *input;
  fmat_t *coeffs;

  if (!PyArg_ParseTuple (args, "O", &input)) {
    return NULL;
  }

  coeffs = PyAubio_ArrayToCFmat (input);

  if (coeffs == NULL) {
    PyErr_SetString (PyExc_ValueError,
        "unable to parse input array");
    return NULL;
  }

  err = aubio_filterbank_set_coeffs (self->o, coeffs);

  if (err > 0) {
    PyErr_SetString (PyExc_ValueError,
        "error when setting filter coefficients");
    return NULL;
  }
  Py_RETURN_NONE;
}
