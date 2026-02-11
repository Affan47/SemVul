PyvtkDataSetAttributes_GetCopyGlobalIds(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "GetCopyGlobalIds");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkDataSetAttributes *op = static_cast<vtkDataSetAttributes *>(vp);

  int temp0 = vtkDataSetAttributes::ALLCOPY;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(0, 1) &&
      (ap.NoArgsLeft() || ap.GetValue(temp0)))
    {
    int tempr = (ap.IsBound() ?
      op->GetCopyGlobalIds(temp0) :
      op->vtkDataSetAttributes::GetCopyGlobalIds(temp0));

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
