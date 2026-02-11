PyvtkPlanesIntersection_PolygonIntersectsBBox(PyObject *, PyObject *args)
{
  vtkPythonArgs ap(args, "PolygonIntersectsBBox");

  double temp0[6];
  double save0[6];
  const int size0 = 6;
  vtkPoints *temp1 = NULL;
  PyObject *result = NULL;

  if (ap.CheckArgCount(2) &&
      ap.GetArray(temp0, size0) &&
      ap.GetVTKObject(temp1, "vtkPoints"))
    {
    ap.SaveArray(temp0, save0, size0);

    int tempr = vtkPlanesIntersection::PolygonIntersectsBBox(temp0, temp1);

    if (ap.ArrayHasChanged(temp0, save0, size0) &&
        !ap.ErrorOccurred())
      {
      ap.SetArray(0, temp0, size0);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
