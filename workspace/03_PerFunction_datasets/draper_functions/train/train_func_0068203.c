PyvtkObjectFactory_SetAllEnableFlags_s2(PyObject *, PyObject *args)
{
  vtkPythonArgs ap(args, "SetAllEnableFlags");

  int temp0;
  char *temp1 = NULL;
  char *temp2 = NULL;
  PyObject *result = NULL;

  if (ap.CheckArgCount(3) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2))
    {
    vtkObjectFactory::SetAllEnableFlags(temp0, temp1, temp2);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
