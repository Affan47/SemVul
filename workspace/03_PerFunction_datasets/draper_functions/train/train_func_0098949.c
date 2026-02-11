PyvtkRenderWindow_GetRGBACharPixelData(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "GetRGBACharPixelData");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkRenderWindow *op = static_cast<vtkRenderWindow *>(vp);

  int temp0;
  int temp1;
  int temp2;
  int temp3;
  int temp4;
  vtkUnsignedCharArray *temp5 = NULL;
  PyObject *result = NULL;

  if (op && !ap.IsPureVirtual() && ap.CheckArgCount(6) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2) &&
      ap.GetValue(temp3) &&
      ap.GetValue(temp4) &&
      ap.GetVTKObject(temp5, "vtkUnsignedCharArray"))
    {
    int tempr = op->GetRGBACharPixelData(temp0, temp1, temp2, temp3, temp4, temp5);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
