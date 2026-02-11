PyvtkFrameBufferObject_SetColorBuffer(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "SetColorBuffer");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkFrameBufferObject *op = static_cast<vtkFrameBufferObject *>(vp);

  unsigned int temp0;
  vtkTextureObject *temp1 = NULL;
  unsigned int temp2 = 0;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(2, 3) &&
      ap.GetValue(temp0) &&
      ap.GetVTKObject(temp1, "vtkTextureObject") &&
      (ap.NoArgsLeft() || ap.GetValue(temp2)))
    {
    if (ap.IsBound())
      {
      op->SetColorBuffer(temp0, temp1, temp2);
      }
    else
      {
      op->vtkFrameBufferObject::SetColorBuffer(temp0, temp1, temp2);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
