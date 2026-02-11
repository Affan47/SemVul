PyvtkConvertSelection_ToSelectionType(PyObject *, PyObject *args)
{
  vtkPythonArgs ap(args, "ToSelectionType");

  vtkSelection *temp0 = NULL;
  vtkDataObject *temp1 = NULL;
  int temp2;
  vtkStringArray *temp3 = 0;
  int temp4 = -1;
  PyObject *result = NULL;

  if (ap.CheckArgCount(3, 5) &&
      ap.GetVTKObject(temp0, "vtkSelection") &&
      ap.GetVTKObject(temp1, "vtkDataObject") &&
      ap.GetValue(temp2) &&
      (ap.NoArgsLeft() || ap.GetVTKObject(temp3, "vtkStringArray")) &&
      (ap.NoArgsLeft() || ap.GetValue(temp4)))
    {
    vtkSelection *tempr = vtkConvertSelection::ToSelectionType(temp0, temp1, temp2, temp3, temp4);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildVTKObject(tempr);
      }
    }

  return result;
}
