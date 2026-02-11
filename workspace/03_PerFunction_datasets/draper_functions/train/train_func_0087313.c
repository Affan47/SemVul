PyvtkXMLDataElement_GetScalarAttribute_s1(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "GetScalarAttribute");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkXMLDataElement *op = static_cast<vtkXMLDataElement *>(vp);

  char *temp0 = NULL;
  int temp1;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(2) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1))
    {
    int tempr = (ap.IsBound() ?
      op->GetScalarAttribute(temp0, temp1) :
      op->vtkXMLDataElement::GetScalarAttribute(temp0, temp1));

    if (!ap.ErrorOccurred())
      {
      ap.SetArgValue(1, temp1);
      }
    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
