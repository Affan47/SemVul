PyvtkGenericCellTessellator_TessellateFace(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "TessellateFace");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkGenericCellTessellator *op = static_cast<vtkGenericCellTessellator *>(vp);

  vtkGenericAdaptorCell *temp0 = NULL;
  vtkGenericAttributeCollection *temp1 = NULL;
  vtkIdType temp2;
  vtkDoubleArray *temp3 = NULL;
  vtkCellArray *temp4 = NULL;
  vtkPointData *temp5 = NULL;
  PyObject *result = NULL;

  if (op && !ap.IsPureVirtual() && ap.CheckArgCount(6) &&
      ap.GetVTKObject(temp0, "vtkGenericAdaptorCell") &&
      ap.GetVTKObject(temp1, "vtkGenericAttributeCollection") &&
      ap.GetValue(temp2) &&
      ap.GetVTKObject(temp3, "vtkDoubleArray") &&
      ap.GetVTKObject(temp4, "vtkCellArray") &&
      ap.GetVTKObject(temp5, "vtkPointData"))
    {
    op->TessellateFace(temp0, temp1, temp2, temp3, temp4, temp5);

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
