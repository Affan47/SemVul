PyvtkOpenFOAMReader_MakeInformationVector(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "MakeInformationVector");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkOpenFOAMReader *op = static_cast<vtkOpenFOAMReader *>(vp);

  vtkInformationVector *temp0 = NULL;
  vtkStdString temp1;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(2) &&
      ap.GetVTKObject(temp0, "vtkInformationVector") &&
      ap.GetValue(temp1))
    {
    int tempr = (ap.IsBound() ?
      op->MakeInformationVector(temp0, temp1) :
      op->vtkOpenFOAMReader::MakeInformationVector(temp0, temp1));

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
