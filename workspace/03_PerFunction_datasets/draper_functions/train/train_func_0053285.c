PyvtkMutableUndirectedGraph_LazyAddEdge_s3(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "LazyAddEdge");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkMutableUndirectedGraph *op = static_cast<vtkMutableUndirectedGraph *>(vp);

  vtkVariant *temp0 = NULL;
  PyObject *pobj0 = NULL;
  vtkIdType temp1;
  vtkVariantArray *temp2 = 0;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(2, 3) &&
      ap.GetSpecialObject(temp0, pobj0, "vtkVariant") &&
      ap.GetValue(temp1) &&
      (ap.NoArgsLeft() || ap.GetVTKObject(temp2, "vtkVariantArray")))
    {
    if (ap.IsBound())
      {
      op->LazyAddEdge(*temp0, temp1, temp2);
      }
    else
      {
      op->vtkMutableUndirectedGraph::LazyAddEdge(*temp0, temp1, temp2);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  Py_XDECREF(pobj0);

  return result;
}
