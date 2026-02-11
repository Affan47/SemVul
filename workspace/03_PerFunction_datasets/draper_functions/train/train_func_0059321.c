PyvtkAbstractPointLocator_FindPointsWithinRadius_s1(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "FindPointsWithinRadius");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkAbstractPointLocator *op = static_cast<vtkAbstractPointLocator *>(vp);

  double temp0;
  double temp1[3];
  const int size1 = 3;
  vtkIdList *temp2 = NULL;
  PyObject *result = NULL;

  if (op && !ap.IsPureVirtual() && ap.CheckArgCount(3) &&
      ap.GetValue(temp0) &&
      ap.GetArray(temp1, size1) &&
      ap.GetVTKObject(temp2, "vtkIdList"))
    {
    op->FindPointsWithinRadius(temp0, temp1, temp2);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
