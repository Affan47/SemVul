PyvtkStructuredGrid_GetPoint_s3(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "GetPoint");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkStructuredGrid *op = static_cast<vtkStructuredGrid *>(vp);

  int temp0;
  int temp1;
  int temp2;
  double temp3[3];
  double save3[3];
  const int size3 = 3;
  bool temp4 = true;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(4, 5) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2) &&
      ap.GetArray(temp3, size3) &&
      (ap.NoArgsLeft() || ap.GetValue(temp4)))
    {
    ap.SaveArray(temp3, save3, size3);

    if (ap.IsBound())
      {
      op->GetPoint(temp0, temp1, temp2, temp3, temp4);
      }
    else
      {
      op->vtkStructuredGrid::GetPoint(temp0, temp1, temp2, temp3, temp4);
      }

    if (ap.ArrayHasChanged(temp3, save3, size3) &&
        !ap.ErrorOccurred())
      {
      ap.SetArray(3, temp3, size3);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
