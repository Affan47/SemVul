PyvtkFastNumericConversion_ConvertFixedPoint(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "ConvertFixedPoint");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkFastNumericConversion *op = static_cast<vtkFastNumericConversion *>(vp);

  double temp0;
  int temp1;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(2) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1))
    {
    int tempr = (ap.IsBound() ?
      op->ConvertFixedPoint(temp0, temp1) :
      op->vtkFastNumericConversion::ConvertFixedPoint(temp0, temp1));

    if (!ap.ErrorOccurred())
      {
      ap.SetArgValue(1, temp1);
      }
    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
