tile (PyObject *self, PyObject *args)
{
  const guint width, height;
  GdkPixbuf *background;

  if (!PyArg_ParseTuple (args, "ii", &width, &height))
    return NULL;

  if (G_UNLIKELY (width == 0 || height == 0)) {
    Py_INCREF (Py_None);
    return Py_None;
  }

  if (TIMAGE (self)->pbuf && (TIMAGE (self)->invalidated ||
                              TIMAGE (self)->width != width ||
                              TIMAGE (self)->height != height))
  {
    TIMAGE (self)->invalidated = FALSE;
    TIMAGE (self)->width = width;
    TIMAGE (self)->height = height;

    background = gdk_pixbuf_new (GDK_COLORSPACE_RGB, TRUE, 8, width, height);
    render_tile (TIMAGE (self)->pbuf, background);

    gtk_image_set_from_pixbuf (GTK_IMAGE (TIMAGE (self)->obj), background);

    g_object_unref (background);
  }

  Py_INCREF (Py_None);
  return Py_None;
}
