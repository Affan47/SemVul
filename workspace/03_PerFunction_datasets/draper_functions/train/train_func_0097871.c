PyvtkIncrementalOctreeNode_GetDistance2ToBoundary_s2(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "GetDistance2ToBoundary");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkIncrementalOctreeNode *op = static_cast<vtkIncrementalOctreeNode *>(vp);

  double temp0[3];
  const int size0 = 3;
  double temp1[3];
  double save1[3];
  const int size1 = 3;
  vtkIncrementalOctreeNode *temp2 = NULL;
  int temp3;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(4) &&
      ap.GetArray(temp0, size0) &&
      ap.GetArray(temp1, size1) &&
      ap.GetVTKObject(temp2, "vtkIncrementalOctreeNode") &&
      ap.GetValue(temp3))
    {
    ap.SaveArray(temp1, save1, size1);

    double tempr = (ap.IsBound() ?
      op->GetDistance2ToBoundary(temp0, temp1, temp2, temp3) :
      op->vtkIncrementalOctreeNode::GetDistance2ToBoundary(temp0, temp1, temp2, temp3));

    if (ap.ArrayHasChanged(temp1, save1, size1) &&
        !ap.ErrorOccurred())
      {
      ap.SetArray(1, temp1, size1);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
