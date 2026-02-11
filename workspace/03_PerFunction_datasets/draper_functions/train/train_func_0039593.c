gdesklets_get_pygobject_type (void)
{
  static PyTypeObject *PyGObject_Type = NULL;

  if (G_UNLIKELY (PyGObject_Type == NULL)) {
    PyObject *module = PyImport_ImportModule("gobject");

    if (!module) goto err_gobject;

    PyObject *moddict = PyModule_GetDict (module);
    PyGObject_Type = (PyTypeObject *) PyDict_GetItemString (moddict, "GObject");

    if (!PyGObject_Type) goto err_gobject;
  }

  return PyGObject_Type;

  err_gobject:
    PyErr_SetString (PyExc_ImportError,
                     "Cannot import name GObject from gobject");
    return NULL;
}
