PyvtkAtom_GetAtomicNumber(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(args, "GetAtomicNumber");
  void *vp = ap.GetSelfPointer(self);
  vtkAtom *op = static_cast<vtkAtom *>(vp);

  PyObject *result = NULL;

  if (ap.CheckArgCount(0))
    {
    unsigned short tempr = op->GetAtomicNumber();

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
