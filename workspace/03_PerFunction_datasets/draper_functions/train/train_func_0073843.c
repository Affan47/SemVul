p_read (void *data, char *ptr, int len)
{
  WRAPPER_DATA *wrap = (WRAPPER_DATA *)data;
  PyObject *buf;
  char *s;

  buf = PyFile_Read (wrap->p_stdin, len);

  if (buf == NULL)
  {
    PyErr_Clear();
    return -1;
  }

  len = PyString_Size(buf);
  s = PyString_AsString(buf);

  memcpy (ptr, s, len);

  Py_DECREF(buf);

  PyErr_Clear();
  return len;
}
