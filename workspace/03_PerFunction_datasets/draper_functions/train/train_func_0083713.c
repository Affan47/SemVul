_wrap_fs_session_list_transmitters (PyGObject *self)
{
  gchar **strv = NULL;
  gint i;
  PyObject *tuple;

  Py_BEGIN_ALLOW_THREADS
  strv = fs_session_list_transmitters (FS_SESSION(self->obj));
  Py_END_ALLOW_THREADS

  if (!strv)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }

  tuple = PyTuple_New (g_strv_length (strv));

  for (i=0; strv[i]; i++)
    PyTuple_SET_ITEM (tuple, i, PyString_FromString(strv[i]));

  g_strfreev (strv);

  return tuple;
}
