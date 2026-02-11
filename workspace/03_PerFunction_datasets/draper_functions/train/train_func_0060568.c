PyvtkXYPlotActor_ViewportToPlotCoordinate_s1(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "ViewportToPlotCoordinate");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkXYPlotActor *op = static_cast<vtkXYPlotActor *>(vp);

  vtkViewport *temp0 = NULL;
  double temp1;
  double temp2;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(3) &&
      ap.GetVTKObject(temp0, "vtkViewport") &&
      ap.GetValue(temp1) &&
      ap.GetValue(temp2))
    {
    if (ap.IsBound())
      {
      op->ViewportToPlotCoordinate(temp0, temp1, temp2);
      }
    else
      {
      op->vtkXYPlotActor::ViewportToPlotCoordinate(temp0, temp1, temp2);
      }

    if (!ap.ErrorOccurred())
      {
      ap.SetArgValue(1, temp1);
      }
    if (!ap.ErrorOccurred())
      {
      ap.SetArgValue(2, temp2);
      }
    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
