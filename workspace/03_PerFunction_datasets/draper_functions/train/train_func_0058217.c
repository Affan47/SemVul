vtkWrapPython_GenerateMethods(
  FILE *fp, const char *classname, ClassInfo *data, HierarchyInfo *hinfo,
  int is_vtkobject, int do_constructors)
{
  int i;
  int fnum;
  int numberOfWrappedFunctions = 0;
  FunctionInfo **wrappedFunctions;
  FunctionInfo *theFunc;
  char *cp;
  const char *ccp;

  wrappedFunctions = (FunctionInfo **)malloc(
    data->NumberOfFunctions*sizeof(FunctionInfo *));


  vtkWrapPython_CustomMethods(fp, classname, data, do_constructors);


  vtkWrap_FindCountHints(data, hinfo);


  vtkWrap_FindNewInstanceMethods(data, hinfo);


  for (i = 0; i < data->NumberOfFunctions; i++)
    {
    theFunc = data->Functions[i];


    if (vtkWrapPython_MethodCheck(theFunc, hinfo) &&
        !theFunc->IsOperator &&
        !vtkWrap_IsDestructor(data, theFunc) &&
        (!vtkWrap_IsConstructor(data, theFunc) == !do_constructors))
      {
      ccp = vtkWrapText_PythonSignature(theFunc);
      cp = (char *)malloc(strlen(ccp)+1);
      strcpy(cp, ccp);
      theFunc->Signature = cp;
      wrappedFunctions[numberOfWrappedFunctions++] = theFunc;
      }
    }


  for (fnum = 0; fnum < numberOfWrappedFunctions; fnum++)
    {
    theFunc = wrappedFunctions[fnum];


    vtkWrapPython_RemovePreceededMethods(
      wrappedFunctions, numberOfWrappedFunctions, fnum);


    if (theFunc->Name)
      {
      fprintf(fp,"\n");

      vtkWrapPython_GenerateOneMethod(
        fp, classname, data, hinfo,
        wrappedFunctions, numberOfWrappedFunctions,
        fnum, is_vtkobject, do_constructors);

      }
    }


  if (!do_constructors)
    {
    vtkWrapPython_ClassMethodDef(fp, classname, data, wrappedFunctions,
                                 numberOfWrappedFunctions, fnum);
    }

  free(wrappedFunctions);
}
