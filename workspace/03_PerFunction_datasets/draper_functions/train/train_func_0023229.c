GetArgAsEnum(PyObject *o, const char *, bool &valid)
{

  int i = 0;
  valid = (vtkPythonGetValue(o, i) != 0);
  return (valid ? i : 0);
}
