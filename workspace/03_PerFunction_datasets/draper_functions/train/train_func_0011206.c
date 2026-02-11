PyvtkHyperOctree_GetPointsOnParentEdge(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "GetPointsOnParentEdge");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkHyperOctree *op = static_cast<vtkHyperOctree *>(vp);

  vtkHyperOctreeCursor *temp0 = NULL;
  int temp1;
  int temp2;
  int temp3;
  int temp4;
  vtkHyperOctreePointsGrabber *temp5 = NULL;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(6) &&
      ap.GetVTKObject(temp0, "vtkHyperOctreeCursor") &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2) &&
      ap.GetValue(temp3) &&
      ap.GetValue(temp4) &&
      ap.GetVTKObject(temp5, "vtkHyperOctreePointsGrabber"))
    {
    if (ap.IsBound())
      {
      op->GetPointsOnParentEdge(temp0, temp1, temp2, temp3, temp4, temp5);
      }
    else
      {
      op->vtkHyperOctree::GetPointsOnParentEdge(temp0, temp1, temp2, temp3, temp4, temp5);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
