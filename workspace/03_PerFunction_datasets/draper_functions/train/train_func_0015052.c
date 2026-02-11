PyvtkCaptionActor2D_SetAttachmentPoint_s1(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "SetAttachmentPoint");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkCaptionActor2D *op = static_cast<vtkCaptionActor2D *>(vp);

  double temp0;
  double temp1;
  double temp2;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(3) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2))
    {
    if (ap.IsBound())
      {
      op->SetAttachmentPoint(temp0, temp1, temp2);
      }
    else
      {
      op->vtkCaptionActor2D::SetAttachmentPoint(temp0, temp1, temp2);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
