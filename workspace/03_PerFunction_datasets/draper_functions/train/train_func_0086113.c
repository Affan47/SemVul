PyvtkIncrementalPointLocator_IsInsertedPoint_s1(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "IsInsertedPoint");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkIncrementalPointLocator *op = static_cast<vtkIncrementalPointLocator *>(vp);

  double temp0;
  double temp1;
  double temp2;
  PyObject *result = NULL;

  if (op && !ap.IsPureVirtual() && ap.CheckArgCount(3) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2))
    {
    vtkIdType tempr = op->IsInsertedPoint(temp0, temp1, temp2);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
