peas_extension_python_dispose (GObject *object)
{
  PeasExtensionPython *pyexten = PEAS_EXTENSION_PYTHON (object);

  if (pyexten->instance)
    {
      PyGILState_STATE state = pyg_gil_state_ensure ();

      Py_DECREF (pyexten->instance);
      pyexten->instance = NULL;

      pyg_gil_state_release (state);
    }

  G_OBJECT_CLASS (peas_extension_python_parent_class)->dispose (object);
}
