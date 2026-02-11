PyvtkMath_SolveQuadratic(PyObject *, PyObject *args)
{
  vtkPythonArgs ap(args, "SolveQuadratic");

  double temp0;
  double temp1;
  double temp2;
  int sizer = 4;
  PyObject *result = NULL;

  if (ap.CheckArgCount(3) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2))
    {
    double *tempr = vtkMath::SolveQuadratic(temp0, temp1, temp2);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildTuple(tempr, sizer);
      }
    }

  return result;
}
