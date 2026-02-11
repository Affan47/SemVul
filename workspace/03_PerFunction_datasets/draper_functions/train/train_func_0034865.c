PyvtkStringArray_LookupValue_s3(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "LookupValue");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkStringArray *op = static_cast<vtkStringArray *>(vp);

  vtkStdString temp0;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(1) &&
      ap.GetValue(temp0))
    {
    vtkIdType tempr = (ap.IsBound() ?
      op->LookupValue(temp0) :
      op->vtkStringArray::LookupValue(temp0));

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
