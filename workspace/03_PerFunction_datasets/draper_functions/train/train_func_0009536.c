PyvtkInteractorObserver_ComputeWorldToDisplay(PyObject *, PyObject *args)
{
  vtkPythonArgs ap(args, "ComputeWorldToDisplay");

  vtkRenderer *temp0 = NULL;
  double temp1;
  double temp2;
  double temp3;
  double temp4[3];
  double save4[3];
  const int size4 = 3;
  PyObject *result = NULL;

  if (ap.CheckArgCount(5) &&
      ap.GetVTKObject(temp0, "vtkRenderer") &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2) &&
      ap.GetValue(temp3) &&
      ap.GetArray(temp4, size4))
    {
    ap.SaveArray(temp4, save4, size4);

    vtkInteractorObserver::ComputeWorldToDisplay(temp0, temp1, temp2, temp3, temp4);

    if (ap.ArrayHasChanged(temp4, save4, size4) &&
        !ap.ErrorOccurred())
      {
      ap.SetArray(4, temp4, size4);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
