PyvtkDataArray_GetDataTypeRange_s2(PyObject *, PyObject *args)
{
  vtkPythonArgs ap(args, "GetDataTypeRange");

  int temp0;
  double temp1[2];
  double save1[2];
  const int size1 = 2;
  PyObject *result = NULL;

  if (ap.CheckArgCount(2) &&
      ap.GetValue(temp0) &&
      ap.GetArray(temp1, size1))
    {
    ap.SaveArray(temp1, save1, size1);

    vtkDataArray::GetDataTypeRange(temp0, temp1);

    if (ap.ArrayHasChanged(temp1, save1, size1) &&
        !ap.ErrorOccurred())
      {
      ap.SetArray(1, temp1, size1);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
