PyvtkLinearTransform_TransformFloatVector_s2(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "TransformFloatVector");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkLinearTransform *op = static_cast<vtkLinearTransform *>(vp);

  float temp0[3];
  const int size0 = 3;
  int sizer = 3;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(1) &&
      ap.GetArray(temp0, size0))
    {
    float *tempr = (ap.IsBound() ?
      op->TransformFloatVector(temp0) :
      op->vtkLinearTransform::TransformFloatVector(temp0));

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildTuple(tempr, sizer);
      }
    }

  return result;
}
