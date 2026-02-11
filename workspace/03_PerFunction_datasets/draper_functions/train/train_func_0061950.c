PyvtkImplicitFunction_EvaluateGradient(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "EvaluateGradient");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkImplicitFunction *op = static_cast<vtkImplicitFunction *>(vp);

  double temp0[3];
  double save0[3];
  const int size0 = 3;
  double temp1[3];
  double save1[3];
  const int size1 = 3;
  PyObject *result = NULL;

  if (op && !ap.IsPureVirtual() && ap.CheckArgCount(2) &&
      ap.GetArray(temp0, size0) &&
      ap.GetArray(temp1, size1))
    {
    ap.SaveArray(temp0, save0, size0);
    ap.SaveArray(temp1, save1, size1);

    op->EvaluateGradient(temp0, temp1);

    if (ap.ArrayHasChanged(temp0, save0, size0) &&
        !ap.ErrorOccurred())
      {
      ap.SetArray(0, temp0, size0);
      }

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
