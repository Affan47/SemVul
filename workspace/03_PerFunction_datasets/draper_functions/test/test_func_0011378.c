PyvtkMath_Dot(PyObject *, PyObject *args)
{
  vtkPythonArgs ap(args, "Dot");

  double temp0[3];
  const int size0 = 3;
  double temp1[3];
  const int size1 = 3;
  PyObject *result = NULL;

  if (ap.CheckArgCount(2) &&
      ap.GetArray(temp0, size0) &&
      ap.GetArray(temp1, size1))
    {
    double tempr = vtkMath::Dot(temp0, temp1);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
