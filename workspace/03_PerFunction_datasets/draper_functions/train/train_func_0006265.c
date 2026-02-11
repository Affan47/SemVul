PyvtkMolecule_AppendAtom_s3(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "AppendAtom");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkMolecule *op = static_cast<vtkMolecule *>(vp);

  unsigned short temp0;
  double temp1;
  double temp2;
  double temp3;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(4) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2) &&
      ap.GetValue(temp3))
    {
    vtkAtom tempr = (ap.IsBound() ?
      op->AppendAtom(temp0, temp1, temp2, temp3) :
      op->vtkMolecule::AppendAtom(temp0, temp1, temp2, temp3));

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildSpecialObject(&tempr, "vtkAtom");
      }
    }

  return result;
}
