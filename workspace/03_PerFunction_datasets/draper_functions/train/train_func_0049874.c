PyvtkOrderedTriangulator_InsertPoint(PyObject *self, PyObject *args)
{
  int nargs = vtkPythonArgs::GetArgCount(self, args);

  switch(nargs)
    {
    case 4:
      return PyvtkOrderedTriangulator_InsertPoint_s1(self, args);
    case 5:
      return PyvtkOrderedTriangulator_InsertPoint_s2(self, args);
    case 6:
      return PyvtkOrderedTriangulator_InsertPoint_s3(self, args);
    }

  vtkPythonArgs::ArgCountError(nargs, "InsertPoint");
  return NULL;
}
