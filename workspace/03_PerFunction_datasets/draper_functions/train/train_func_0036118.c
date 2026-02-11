PyvtkMINCImageAttributes_SetAttributeValueAsInt(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "SetAttributeValueAsInt");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkMINCImageAttributes *op = static_cast<vtkMINCImageAttributes *>(vp);

  char *temp0 = NULL;
  char *temp1 = NULL;
  int temp2;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(3) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2))
    {
    if (ap.IsBound())
      {
      op->SetAttributeValueAsInt(temp0, temp1, temp2);
      }
    else
      {
      op->vtkMINCImageAttributes::SetAttributeValueAsInt(temp0, temp1, temp2);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
