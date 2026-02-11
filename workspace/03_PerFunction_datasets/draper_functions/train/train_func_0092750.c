PyvtkRayCastImageDisplayHelper_RenderTexture(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "RenderTexture");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkRayCastImageDisplayHelper *op = static_cast<vtkRayCastImageDisplayHelper *>(vp);

  vtkVolume *temp0 = NULL;
  vtkRenderer *temp1 = NULL;
  vtkFixedPointRayCastImage *temp2 = NULL;
  float temp3;
  PyObject *result = NULL;

  if (op && !ap.IsPureVirtual() && ap.CheckArgCount(4) &&
      ap.GetVTKObject(temp0, "vtkVolume") &&
      ap.GetVTKObject(temp1, "vtkRenderer") &&
      ap.GetVTKObject(temp2, "vtkFixedPointRayCastImage") &&
      ap.GetValue(temp3))
    {
    op->RenderTexture(temp0, temp1, temp2, temp3);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
