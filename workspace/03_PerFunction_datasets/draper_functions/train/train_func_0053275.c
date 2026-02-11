PyvtkOpenGLRenderWindow_SetRGBACharPixelData(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "SetRGBACharPixelData");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkOpenGLRenderWindow *op = static_cast<vtkOpenGLRenderWindow *>(vp);

  int temp0;
  int temp1;
  int temp2;
  int temp3;
  vtkUnsignedCharArray *temp4 = NULL;
  int temp5;
  int temp6 = 0;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(6, 7) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2) &&
      ap.GetValue(temp3) &&
      ap.GetVTKObject(temp4, "vtkUnsignedCharArray") &&
      ap.GetValue(temp5) &&
      (ap.NoArgsLeft() || ap.GetValue(temp6)))
    {
    int tempr = (ap.IsBound() ?
      op->SetRGBACharPixelData(temp0, temp1, temp2, temp3, temp4, temp5, temp6) :
      op->vtkOpenGLRenderWindow::SetRGBACharPixelData(temp0, temp1, temp2, temp3, temp4, temp5, temp6));

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
