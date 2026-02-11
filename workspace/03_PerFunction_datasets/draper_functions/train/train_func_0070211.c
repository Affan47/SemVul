find_python_extension_type (PeasPluginInfo *info,
                            GType           exten_type,
                            PyObject       *pymodule)
{
  PyObject *pygtype, *pytype;
  PyObject *locals, *key, *value;
  Py_ssize_t pos = 0;

  locals = PyModule_GetDict (pymodule);

  pygtype = pyg_type_wrapper_new (exten_type);
  pytype = PyObject_GetAttrString (pygtype, "pytype");
  g_warn_if_fail (pytype != NULL);

  if (pytype != NULL && pytype != Py_None)
    {
      while (PyDict_Next (locals, &pos, &key, &value))
        {
          if (!PyType_Check (value))
            continue;

          switch (PyObject_IsSubclass (value, pytype))
            {
            case 1:
              Py_DECREF (pygtype);
              return (PyTypeObject *) value;
            case 0:
              continue;
            case -1:
            default:
              PyErr_Print ();
              continue;
            }
        }
    }

  Py_DECREF (pygtype);

  return NULL;
}
