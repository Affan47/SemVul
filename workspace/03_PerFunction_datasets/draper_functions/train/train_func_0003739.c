pyGcomprisSoundCallback(gchar *file){
  PyObject* result;
  PyObject* py_cb;

  g_warning("python sound callback : %s", file);

  PyGILState_STATE gil;

  g_assert ( py_sound_callbacks != NULL);

  py_cb = g_hash_table_lookup(py_sound_callbacks, file);


  if(py_cb==NULL) return;

  if (!Py_IsInitialized())
    return;

  gil = pyg_gil_state_ensure();

  result = PyObject_CallFunction(py_cb, "O", PyString_FromString(file));


  Py_DECREF(py_cb);

  if(result==NULL){
    PyErr_Print();
  } else {
    Py_DECREF(result);
  }

  pyg_gil_state_release(gil);

}
