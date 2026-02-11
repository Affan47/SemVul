PyvtkAxisActor2D_GetAdjustedRange_s1(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "GetAdjustedRange");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkAxisActor2D *op = static_cast<vtkAxisActor2D *>(vp);

  double temp0;
  double temp1;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(2) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1))
    {
    if (ap.IsBound())
      {
      op->GetAdjustedRange(temp0, temp1);
      }
    else
      {
      op->vtkAxisActor2D::GetAdjustedRange(temp0, temp1);
      }

    if (!ap.ErrorOccurred())
      {
      ap.SetArgValue(0, temp0);
      }
    if (!ap.ErrorOccurred())
      {
      ap.SetArgValue(1, temp1);
      }
    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
