PyvtkDataObject_SetPointDataActiveScalarInfo(PyObject *, PyObject *args)
{
  vtkPythonArgs ap(args, "SetPointDataActiveScalarInfo");

  vtkInformation *temp0 = NULL;
  int temp1;
  int temp2;
  PyObject *result = NULL;

  if (ap.CheckArgCount(3) &&
      ap.GetVTKObject(temp0, "vtkInformation") &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2))
    {
    vtkDataObject::SetPointDataActiveScalarInfo(temp0, temp1, temp2);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
