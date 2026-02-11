py_gc_set_background(PyObject* self, PyObject* args)
{
  PyObject* pyCanvasGroup;
  GooCanvasItem* canvasGroup;
  gchar* file;


  if(!PyArg_ParseTuple(args, "Os:gc_set_background", &pyCanvasGroup, &file))
    return NULL;
  canvasGroup = (GooCanvasItem*) pygobject_get(pyCanvasGroup);


  gc_set_background(canvasGroup, file);

  return Py_None;
}
