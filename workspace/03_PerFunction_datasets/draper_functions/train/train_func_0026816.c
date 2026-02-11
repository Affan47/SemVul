PyVTKAddFile_vtkvmtkSimplifyVoronoiDiagram(
  PyObject *dict, const char *modulename)
{
  PyObject *o;
  o = PyVTKClass_vtkvmtkSimplifyVoronoiDiagramNew(modulename);

  if (o && PyDict_SetItemString(dict, (char *)"vtkvmtkSimplifyVoronoiDiagram", o) != 0)
    {
    Py_DECREF(o);
    }

  o = PyInt_FromLong(0);
  if (o && PyDict_SetItemString(dict, (char *)"VTK_VMTK_REMOVE_BOUNDARY_POINTS", o) != 0)
    {
    Py_DECREF(o);
    }

  o = PyInt_FromLong(1);
  if (o && PyDict_SetItemString(dict, (char *)"VTK_VMTK_REMOVE_BOUNDARY_CELLS", o) != 0)
    {
    Py_DECREF(o);
    }

}
