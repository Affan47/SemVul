PyvtkStreamer_GetStartLocation(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "GetStartLocation");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkStreamer *op = static_cast<vtkStreamer *>(vp);

  int temp0;
  double temp1[3];
  double save1[3];
  const int size1 = 3;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(2) &&
      ap.GetValue(temp0) &&
      ap.GetArray(temp1, size1))
    {
    ap.SaveArray(temp1, save1, size1);

    vtkIdType tempr = (ap.IsBound() ?
      op->GetStartLocation(temp0, temp1) :
      op->vtkStreamer::GetStartLocation(temp0, temp1));

    if (!ap.ErrorOccurred())
      {
      ap.SetArgValue(0, temp0);
      }
    if (ap.ArrayHasChanged(temp1, save1, size1) &&
        !ap.ErrorOccurred())
      {
      ap.SetArray(1, temp1, size1);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
