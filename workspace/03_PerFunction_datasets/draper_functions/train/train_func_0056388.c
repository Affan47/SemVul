add_constant(const char *name, const char *value,
                  unsigned int type, const char *typeclass, int flag)
{
  ValueInfo *con = (ValueInfo *)malloc(sizeof(ValueInfo));
  vtkParse_InitValue(con);
  con->ItemType = VTK_CONSTANT_INFO;
  con->Name = vtkstrdup(name);
  con->Value = vtkstrdup(value);
  con->Type = type;
  if (typeclass)
    {
    con->Class = vtkstrdup(typeclass);
    }

  if (flag == 2)
    {
    con->IsEnum = 1;
    }

  if (flag == 1)
    {
    con->Access = VTK_ACCESS_PUBLIC;
    if (con->Type == 0)
      {
      con->Type = guess_constant_type(con->Value);
      }
    vtkParse_AddConstantToNamespace(data.Contents, con);
    }
  else if (currentClass)
    {
    con->Access = access_level;
    vtkParse_AddConstantToClass(currentClass, con);
    }
  else
    {
    con->Access = VTK_ACCESS_PUBLIC;
    vtkParse_AddConstantToNamespace(currentNamespace, con);
    }
}
