PyvtkOpenGLPolyDataMapper_Draw(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "Draw");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkOpenGLPolyDataMapper *op = static_cast<vtkOpenGLPolyDataMapper *>(vp);

  vtkRenderer *temp0 = NULL;
  vtkActor *temp1 = NULL;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(2) &&
      ap.GetVTKObject(temp0, "vtkRenderer") &&
      ap.GetVTKObject(temp1, "vtkActor"))
    {
    int tempr = (ap.IsBound() ?
      op->Draw(temp0, temp1) :
      op->vtkOpenGLPolyDataMapper::Draw(temp0, temp1));

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
