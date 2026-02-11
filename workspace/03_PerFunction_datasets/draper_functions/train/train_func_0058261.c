vtkWrapPython_ExportVTKClass(
  FILE *fp, ClassInfo *data, HierarchyInfo *hinfo)
{
  char classname[1024];
  const char *supername;


  vtkWrapPython_PythonicName(data->Name, classname);


  fprintf(fp,
          "#if defined(WIN32)\n"
          "extern \"C\" { __declspec( dllexport ) PyObject *PyVTKClass_%sNew(const char *); }\n"
          "#else\n"
          "extern \"C\" { PyObject *PyVTKClass_%sNew(const char *); }\n"
          "#endif\n"
          "\n",
          classname, classname);


  supername = vtkWrapPython_GetSuperClass(data, hinfo);
  if (supername)
    {
    vtkWrapPython_PythonicName(supername, classname);
    fprintf(fp,
      "#ifndef DECLARED_PyVTKClass_%sNew\n"
      "extern \"C\" { PyObject *PyVTKClass_%sNew(const char *); }\n"
      "#define DECLARED_PyVTKClass_%sNew\n"
      "#endif\n",
      classname, classname, classname);
    }
}
