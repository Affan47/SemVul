PyVTKAddFile_vtkLandmarkTransform(
  PyObject *dict, const char *modulename)
{
  PyObject *o;
  o = PyVTKClass_vtkLandmarkTransformNew(modulename);

  if (o && PyDict_SetItemString(dict, (char *)"vtkLandmarkTransform", o) != 0)
    {
    Py_DECREF(o);
    }

  o = PyInt_FromLong(6);
  if (o && PyDict_SetItemString(dict, (char *)"VTK_LANDMARK_RIGIDBODY", o) != 0)
    {
    Py_DECREF(o);
    }

  o = PyInt_FromLong(7);
  if (o && PyDict_SetItemString(dict, (char *)"VTK_LANDMARK_SIMILARITY", o) != 0)
    {
    Py_DECREF(o);
    }

  o = PyInt_FromLong(12);
  if (o && PyDict_SetItemString(dict, (char *)"VTK_LANDMARK_AFFINE", o) != 0)
    {
    Py_DECREF(o);
    }

}
