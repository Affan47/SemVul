PyvtkExodusIICacheKey_vtkExodusIICacheKey_s2(PyObject *, PyObject *args)
{
  vtkPythonArgs ap(args, "vtkExodusIICacheKey");

  int temp0;
  int temp1;
  int temp2;
  int temp3;
  PyObject *result = NULL;

  if (ap.CheckArgCount(4) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2) &&
      ap.GetValue(temp3))
    {
    vtkExodusIICacheKey *op = new vtkExodusIICacheKey(temp0, temp1, temp2, temp3);

    result = PyVTKSpecialObject_New("vtkExodusIICacheKey", op);
    }

  return result;
}
