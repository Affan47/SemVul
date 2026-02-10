PyvtkvmtkPolyDataBranchUtilities_ExtractGroup(PyObject *, PyObject *args)
{
  vtkPythonArgs ap(args, "ExtractGroup");

  vtkPolyData *temp0 = NULL;
  char *temp1 = NULL;
  vtkIdType temp2;
  bool temp3 = false;
  vtkPolyData *temp4 = NULL;
  PyObject *result = NULL;

  if (ap.CheckArgCount(5) &&
      ap.GetVTKObject(temp0, "vtkPolyData") &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2) &&
      ap.GetValue(temp3) &&
      ap.GetVTKObject(temp4, "vtkPolyData"))
    {
    vtkvmtkPolyDataBranchUtilities::ExtractGroup(temp0, temp1, temp2, temp3, temp4);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
