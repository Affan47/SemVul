quicksearch_clear(PyObject *self, PyObject *args)
{
  QuickSearch *qs;
  MainWindow *mainwin;

  mainwin = mainwindow_get_mainwindow();
  if(!mainwin || !mainwin->summaryview || !mainwin->summaryview->quicksearch) {
    PyErr_SetString(PyExc_LookupError, "Quicksearch not found");
    return NULL;
  }

  qs = mainwin->summaryview->quicksearch;
  quicksearch_set(qs, prefs_common.summary_quicksearch_type, "");

  Py_INCREF(Py_None);
  return Py_None;
}
