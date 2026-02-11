set_from_file (PyObject *self, PyObject *args)
{
  gchar *filename;
  GdkPixbuf *alphaified;
  GError *error = NULL;

  if (!PyArg_ParseTuple (args, "s", &filename))
    return NULL;


  if (G_LIKELY (TIMAGE (self)->pbuf))
    g_object_unref (TIMAGE (self)->pbuf);


  if (!G_UNLIKELY (TIMAGE (self)->pbuf = gdk_pixbuf_new_from_file (filename,
                                                                   &error)))
  {
    PyErr_SetString(PyExc_RuntimeError, error->message);
    g_error_free (error);
    return NULL;
  }


  alphaified = gdk_pixbuf_add_alpha (TIMAGE (self)->pbuf, FALSE, 0, 0, 0);
  g_object_unref (TIMAGE (self)->pbuf);

  TIMAGE (self)->pbuf = alphaified;
  TIMAGE (self)->invalidated = TRUE;

  Py_INCREF (Py_None);
  return Py_None;
}
