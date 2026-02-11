PyvtkRowQuery_NextRow_s1(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "NextRow");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkRowQuery *op = static_cast<vtkRowQuery *>(vp);

  PyObject *result = NULL;

  if (op && !ap.IsPureVirtual() && ap.CheckArgCount(0))
    {
    bool tempr = op->NextRow();

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
