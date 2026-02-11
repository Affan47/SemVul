py_gc_skin_pixmap_load(PyObject* self, PyObject* args)
{
  char* pixmapfile;
  GdkPixbuf* result;
  PyObject* pyresult;


  if(!PyArg_ParseTuple(args, "s:gc_skin_pixmap_load", &pixmapfile))
    return NULL;


  result = gc_skin_pixmap_load(pixmapfile);


  pyresult = (PyObject*) pygobject_new((GObject*) result);

#if GDK_PIXBUF_MAJOR <= 2 && GDK_PIXBUF_MINOR <= 24
  gdk_pixbuf_unref(result);
#else
  g_object_unref(result);
#endif

  return(pyresult);
}
