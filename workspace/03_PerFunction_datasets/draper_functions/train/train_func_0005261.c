PyvtkModelMetadata_AddQARecord(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "AddQARecord");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkModelMetadata *op = static_cast<vtkModelMetadata *>(vp);

  char *temp0 = NULL;
  char *temp1 = NULL;
  char *temp2 = NULL;
  char *temp3 = NULL;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(4) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2) &&
      ap.GetValue(temp3))
    {
    if (ap.IsBound())
      {
      op->AddQARecord(temp0, temp1, temp2, temp3);
      }
    else
      {
      op->vtkModelMetadata::AddQARecord(temp0, temp1, temp2, temp3);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
