PyvtkSpline_Evaluate(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "Evaluate");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkSpline *op = static_cast<vtkSpline *>(vp);

  double temp0;
  PyObject *result = NULL;

  if (op && !ap.IsPureVirtual() && ap.CheckArgCount(1) &&
      ap.GetValue(temp0))
    {
    double tempr = op->Evaluate(temp0);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
