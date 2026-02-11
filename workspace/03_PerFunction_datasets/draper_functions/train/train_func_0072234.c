PyvtkContourGrid_GenerateValues(PyObject *self, PyObject *args)
{
  int nargs = vtkPythonArgs::GetArgCount(self, args);

  switch(nargs)
    {
    case 2:
      return PyvtkContourGrid_GenerateValues_s1(self, args);
    case 3:
      return PyvtkContourGrid_GenerateValues_s2(self, args);
    }

  vtkPythonArgs::ArgCountError(nargs, "GenerateValues");
  return NULL;
}
