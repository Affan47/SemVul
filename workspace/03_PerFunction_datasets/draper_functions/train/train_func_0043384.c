vtkWrapText_PythonTypeSignature(
  struct vtkWPString *result, const char *braces[2], ValueInfo *arg)
{
  char text[32];
  const char *dimension;
  const char *classname = "";

  if (vtkWrap_IsVoid(arg))
    {
    classname = "void";
    }
  else if (vtkWrap_IsObject(arg))
    {
    classname = arg->Class;
    }
  else if (vtkWrap_IsFunction(arg))
    {
    classname = "function";
    }
  else if (vtkWrap_IsString(arg) || vtkWrap_IsCharPointer(arg))
    {
    classname = "string";
    if ((arg->Type & VTK_PARSE_BASE_TYPE) == VTK_PARSE_UNICODE_STRING)
      {
      classname = "unicode";
      }
    }
  else if (vtkWrap_IsChar(arg))
    {
    classname = "char";
    }
  else if (vtkWrap_IsBool(arg))
    {
    classname = "bool";
    }
  else if (vtkWrap_IsRealNumber(arg))
    {
    classname = "float";
    }
  else if (vtkWrap_IsInteger(arg))
    {
    classname = "int";
    }

  if (vtkWrap_IsArray(arg))
    {
    if (arg->CountHint)
      {
      vtkWPString_Append(result, braces[0]);
      vtkWPString_Append(result, classname);
      vtkWPString_Append(result, ", ...");
      vtkWPString_Append(result, braces[1]);
      }
    else
      {
      sprintf(text, "%d", arg->Count);
      dimension = text;
      vtkWrapText_PythonArraySignature(result, classname, braces,
        1, &dimension);
      }
    }
  else if (vtkWrap_IsNArray(arg))
    {
    vtkWrapText_PythonArraySignature(result, classname, braces,
      arg->NumberOfDimensions, arg->Dimensions);
    }
  else
    {
    vtkWPString_Append(result, classname);
    }
}
