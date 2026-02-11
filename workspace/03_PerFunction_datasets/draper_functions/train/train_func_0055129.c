PyvtkTextureObject_Create3D_s2(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "Create3D");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkTextureObject *op = static_cast<vtkTextureObject *>(vp);

  unsigned int temp0;
  unsigned int temp1;
  unsigned int temp2;
  int temp3;
  int temp4;
  bool temp5 = false;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(6) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2) &&
      ap.GetValue(temp3) &&
      ap.GetValue(temp4) &&
      ap.GetValue(temp5))
    {
    bool tempr = (ap.IsBound() ?
      op->Create3D(temp0, temp1, temp2, temp3, temp4, temp5) :
      op->vtkTextureObject::Create3D(temp0, temp1, temp2, temp3, temp4, temp5));

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
