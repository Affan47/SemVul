PyvtkTimePointUtility_DateTimeToTimePoint(PyObject *, PyObject *args)
{
  vtkPythonArgs ap(args, "DateTimeToTimePoint");

  int temp0;
  int temp1;
  int temp2;
  int temp3;
  int temp4;
  int temp5;
  int temp6 = 0;
  PyObject *result = NULL;

  if (ap.CheckArgCount(6, 7) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2) &&
      ap.GetValue(temp3) &&
      ap.GetValue(temp4) &&
      ap.GetValue(temp5) &&
      (ap.NoArgsLeft() || ap.GetValue(temp6)))
    {
    unsigned long long tempr = vtkTimePointUtility::DateTimeToTimePoint(temp0, temp1, temp2, temp3, temp4, temp5, temp6);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
