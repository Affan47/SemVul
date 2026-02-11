PyvtkSQLDatabase_EffectSchema(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "EffectSchema");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkSQLDatabase *op = static_cast<vtkSQLDatabase *>(vp);

  vtkSQLDatabaseSchema *temp0 = NULL;
  bool temp1 = false;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(1, 2) &&
      ap.GetVTKObject(temp0, "vtkSQLDatabaseSchema") &&
      (ap.NoArgsLeft() || ap.GetValue(temp1)))
    {
    bool tempr = (ap.IsBound() ?
      op->EffectSchema(temp0, temp1) :
      op->vtkSQLDatabase::EffectSchema(temp0, temp1));

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
