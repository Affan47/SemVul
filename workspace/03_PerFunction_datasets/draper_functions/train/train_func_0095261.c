PyVTKAddFile_vtkDataSetGradientPrecompute(
  PyObject *dict, const char *modulename)
{
  PyObject *o;
  o = PyVTKClass_vtkDataSetGradientPrecomputeNew(modulename);

  if (o && PyDict_SetItemString(dict, (char *)"vtkDataSetGradientPrecompute", o) != 0)
    {
    Py_DECREF(o);
    }

}
