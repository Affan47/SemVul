PyvtkPainterDeviceAdapter_DrawArrays(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "DrawArrays");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkPainterDeviceAdapter *op = static_cast<vtkPainterDeviceAdapter *>(vp);

  int temp0;
  vtkIdType temp1;
  vtkIdType temp2;
  PyObject *result = NULL;

  if (op && !ap.IsPureVirtual() && ap.CheckArgCount(3) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2))
    {
    op->DrawArrays(temp0, temp1, temp2);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
