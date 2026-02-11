PyvtkMolecule_AppendAtom_s2(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "AppendAtom");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkMolecule *op = static_cast<vtkMolecule *>(vp);

  unsigned short temp0;
  vtkVector3f *temp1 = NULL;
  PyObject *pobj1 = NULL;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(2) &&
      ap.GetValue(temp0) &&
      ap.GetSpecialObject(temp1, pobj1, "vtkVector3f"))
    {
    vtkAtom tempr = (ap.IsBound() ?
      op->AppendAtom(temp0, *temp1) :
      op->vtkMolecule::AppendAtom(temp0, *temp1));

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildSpecialObject(&tempr, "vtkAtom");
      }
    }

  Py_XDECREF(pobj1);

  return result;
}
