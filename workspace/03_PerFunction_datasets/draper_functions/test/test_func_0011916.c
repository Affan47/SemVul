PyvtkVector_IfLi3EE_Normalize(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(args, "Normalize");
  void *vp = ap.GetSelfPointer(self);
  vtkVector<float, 3> *op = static_cast<vtkVector<float, 3> *>(vp);

  PyObject *result = NULL;

  if (ap.CheckArgCount(0))
    {
    double tempr = op->Normalize();

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
