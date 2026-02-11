PyvtkGraph_SetEdgePoint_s1(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "SetEdgePoint");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkGraph *op = static_cast<vtkGraph *>(vp);

  vtkIdType temp0;
  vtkIdType temp1;
  double temp2[3];
  double save2[3];
  const int size2 = 3;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(3) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetArray(temp2, size2))
    {
    ap.SaveArray(temp2, save2, size2);

    if (ap.IsBound())
      {
      op->SetEdgePoint(temp0, temp1, temp2);
      }
    else
      {
      op->vtkGraph::SetEdgePoint(temp0, temp1, temp2);
      }

    if (ap.ArrayHasChanged(temp2, save2, size2) &&
        !ap.ErrorOccurred())
      {
      ap.SetArray(2, temp2, size2);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
