PyvtkUnstructuredGridVolumeZSweepMapper_GetMaximumImageSampleDistanceMaxValue(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "GetMaximumImageSampleDistanceMaxValue");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkUnstructuredGridVolumeZSweepMapper *op = static_cast<vtkUnstructuredGridVolumeZSweepMapper *>(vp);

  PyObject *result = NULL;

  if (op && ap.CheckArgCount(0))
    {
    float tempr = (ap.IsBound() ?
      op->GetMaximumImageSampleDistanceMaxValue() :
      op->vtkUnstructuredGridVolumeZSweepMapper::GetMaximumImageSampleDistanceMaxValue());

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
