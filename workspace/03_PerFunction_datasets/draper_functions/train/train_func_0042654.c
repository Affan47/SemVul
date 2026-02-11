PyvtkIncrementalOctreePointLocator_InitPointInsertion_s1(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "InitPointInsertion");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkIncrementalOctreePointLocator *op = static_cast<vtkIncrementalOctreePointLocator *>(vp);

  vtkPoints *temp0 = NULL;
  double temp1[6];
  const int size1 = 6;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(2) &&
      ap.GetVTKObject(temp0, "vtkPoints") &&
      ap.GetArray(temp1, size1))
    {
    int tempr = (ap.IsBound() ?
      op->InitPointInsertion(temp0, temp1) :
      op->vtkIncrementalOctreePointLocator::InitPointInsertion(temp0, temp1));

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
